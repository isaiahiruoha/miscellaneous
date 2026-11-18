import numpy as np
import matplotlib.pyplot as plt

from activation import activation 
from weighted_sum import weighted_sum
from activation_gradient import activation_gradient
from compute_gradient_for_weights_and_one_layer_below import compute_gradient_for_weights_and_one_layer_below

np.random.seed(0)

# %% prepare data and initialize the network

# Generate 1000 training data points

X_all = np.column_stack((0.001 * np.arange(1, 1001), 0.001 * (1000 - np.arange(1, 1001)))) # shape [1000, 2]
y_all = np.cos(3 * np.pi * X_all[:, 0]) + np.sin(np.pi * X_all[:, 1]) + 2 #shape [1000, 1]
y_all = y_all.reshape(-1, 1)
n_sample = X_all.shape[0]

# Initialization network parameters.
# The training data are split to many "batches".
# In this lab, each batch has 50 data points
# Model training (the forward-backward propagation)
# is performed on batch-by-batch.

batch_size = 50
W1 = 0.01 * np.random.randn(2, 256) # shape [2, 256]
W2 = 0.01 * np.random.randn(256, 256) # shape [256, 256]
W3 = 0.01 * np.random.randn(256, 1) # shape [256, 1]


# variables for optimization algorithm: AdamSGD
# for this lab, you do not have to know them
# just regard optimizer as a function (blackbox).

m_W1 = np.zeros_like(W1)
v_W1 = np.zeros_like(W1)
m_W2 = np.zeros_like(W2)
v_W2 = np.zeros_like(W2)
m_W3 = np.zeros_like(W3)
v_W3 = np.zeros_like(W3)
step = 0

# %% start training

# prepare to visulize the results
plt.ion()
fig, ax = plt.subplots()

# An epoch means an iteration over all 1000 training data points.
# we let the program to finish after 550 epoches.

for epoch in range(1, 551):

    #permute the training dataset for each epoch
    perm = np.random.permutation(1000)
    Xp = X_all[perm]
    yp = y_all[perm]
    
    total_error = 0
    y_pred = np.zeros((n_sample, 1)) # variable that saves the prediction
    
    for i in range(n_sample // batch_size):

        # %% Prepare data for the current batch
        d_start = i * batch_size
        X_batch = Xp[d_start:d_start + batch_size]
        y_batch = yp[d_start:d_start + batch_size]

        # %% ---------------------FORWARD PROPAGATION------------------- 
        X = X_batch # dense1
        layer1_alpha = weighted_sum(X, W1)
        layer1_h = activation(layer1_alpha)
        
        layer2_alpha = weighted_sum(layer1_h, W2)
        layer2_h = activation(layer2_alpha)

        output_layer_alpha = weighted_sum(layer2_h, W3)
        output_layer = output_layer_alpha

        error = np.mean((output_layer - y_batch) ** 2)

        # %% BACKPROPAGATION

        output_layer_gradient = 2 * (output_layer - y_batch) / batch_size

        # calculate gradients w.r.t. W3 and h2 (see defination of W3 and h2 in the figure of the handout) 
        W3_gradient, layer2_h_gradient = compute_gradient_for_weights_and_one_layer_below(output_layer_gradient, W3, layer2_h)
        
        # add some code below
        # to calculate gradients of error w.r.t. alpha_2 (see defination of alpha_2 in the figure of the handout)
        
        layer2_alpha_gradient = activation_gradient(layer2_h) * layer2_h_gradient
     
        # calculate gradients w.r.t. W2 and h1 (see defination of W3 and h2 in the figure of the handout) 
                
        W2_gradient, layer1_h_gradient = compute_gradient_for_weights_and_one_layer_below(layer2_alpha_gradient, W2, layer1_h)

        # add some code below
        # to calculate gradients of error w.r.t. alpha_1 (see defination of alpha_1 in the figure of the handout)
        layer1_alpha_gradient = activation_gradient(layer1_h) * layer1_h_gradient

        # calculate gradients w.r.t. W1 and X (see defination of W1 in the figure of the handout) 
        W1_gradient, _ = compute_gradient_for_weights_and_one_layer_below(layer1_alpha_gradient, W1, X)

        # update error and prediction
        total_error += error
        y_pred[d_start:d_start + batch_size] = output_layer

        # %% UPDATE (Adam optimizer)

        # Using optimizer: Adam SGD
        # For reference see: https://arxiv.org/abs/1412.6980
        # for this lab, you do not have to know it
        # just regard optimizer as a function (blackbox).

        step += 1
        lr = 0.01
        beta1 = 0.9
        beta2 = 0.999
        eps = 1e-8

        # W1 update
        m_W1 = beta1 * m_W1 + (1 - beta1) * W1_gradient
        v_W1 = beta2 * v_W1 + (1 - beta2) * (W1_gradient ** 2)
        m_hat_W1 = m_W1 / (1 - beta1 ** step)
        v_hat_W1 = v_W1 / (1 - beta2 ** step)
        W1 -= lr * m_hat_W1 / (np.sqrt(v_hat_W1) + eps)

        # W2 update
        m_W2 = beta1 * m_W2 + (1 - beta1) * W2_gradient
        v_W2 = beta2 * v_W2 + (1 - beta2) * (W2_gradient ** 2)
        m_hat_W2 = m_W2 / (1 - beta1 ** step)
        v_hat_W2 = v_W2 / (1 - beta2 ** step)
        W2 -= lr * m_hat_W2 / (np.sqrt(v_hat_W2) + eps)

        # W3 update
        m_W3 = beta1 * m_W3 + (1 - beta1) * W3_gradient
        v_W3 = beta2 * v_W3 + (1 - beta2) * (W3_gradient ** 2)
        m_hat_W3 = m_W3 / (1 - beta1 ** step)
        v_hat_W3 = v_W3 / (1 - beta2 ** step)
        W3 -= lr * m_hat_W3 / (np.sqrt(v_hat_W3) + eps)

    # visulize the results
    ax.clear()
    ax.plot(X_all[:, 0], y_all, 'o', label='True')
    ax.plot(Xp[:, 0], y_pred, '.', label='Predicted')
    ax.set_xlim([-0.1, 1.1])
    ax.set_ylim([0.5, 4.5])
    ax.set_title(f"Epoch {epoch}\n Squared Loss = {total_error * batch_size / n_sample:.4f}")
    ax.legend()
    plt.pause(0.01)

plt.ioff()
plt.show()