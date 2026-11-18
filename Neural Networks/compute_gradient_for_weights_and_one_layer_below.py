import numpy as np

def compute_gradient_for_weights_and_one_layer_below(RG, W, X):

    # RG: received gradient  [batch_size, out_dim]
    # W:  layer weight       [in_dim, out_dim]
    # X:  layer input        [batch_size, in_dim]

    # W_grad: gradient for W   [in_dim, out_dim]
    # X_grad: gradient for X   [batch_size, in_dim]

    # please refer to the lab hand-out and think why it make sense.

    W_grad = np.dot(X.T, RG)    
    h_grad = np.dot(RG, W.T)  
    return W_grad, h_grad
