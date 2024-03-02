import os
import uuid

import cohere  # Importing cohere library

# Retrieving the API key from the environment variables
co = cohere.Client(str(os.environ.get("COHERE_KEY"))) 

# Initializing variables
user_input = ""  # User input
conversation_id = str(uuid.uuid64())  # Unique ID for conversation
MAX_TURNS = 10  # Maximum number of conversation turns

# Loop for conversation turns
for i in range(MAX_TURNS):
    user_input = input("User: ")  # Taking user input
    
    if user_input.lower() == "stop":  # If user inputs "stop", break the loop
        break
    
    # Getting response from the chatbot
    response = co.chat(
        user_input,
        model="command-nightly",  # Specifying the model to use
        conversation_id=conversation_id,  # Passing conversation ID for continuity
        search_queries_only=True, # Only search for queries
    )

    # Printing the response from the chatbot
    print(
        "\nChatBot:\n", 
          " && ".join(q["text"] for q in response.search.queries),
          "\n\n")  # Newlines for readability
