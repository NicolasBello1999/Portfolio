import numpy as np
import random
import string
from keras.models import Sequential
from keras.layers import Embedding, LSTM, Dense
from keras.preprocessing.text import Tokenizer
from keras.preprocessing.sequence import pad_sequences

# Set the seed for reproducibility
np.random.seed(42)
random.seed(42)

# A small dataset of 3 correct words
correct_words = ["apple", "submarine", "orange"]

def oneCharEdits(word):
    alphabet = string.ascii_lowercase
    wordSplits = [(word[:x], word[x:]) for x in range(len(word) + 1)]
    wordDeletes = [l + r[1:] for l,r in wordSplits if r]
    wordSwaps = [l + r[1] + r[0] + r[2:] for l,r in wordSplits if len(r) > 1]
    wordReplaces = [l + c + r[1:] for l,r in wordSplits if r for c in alphabet]
    wordInserts = [l + c + r for l,r in wordSplits for c in alphabet]

    return set(wordDeletes + wordSwaps + wordReplaces + wordInserts)

def twoCharEdits(word):
    return set(w2 for w1 in oneCharEdits(word) for w2 in oneCharEdits(w1))

def generate_dataset(correct_words):
    dataset = []
    for word in correct_words:
        misspellings = list(twoCharEdits(word))  # Convert set to list
        for misspelled_word in misspellings:
            dataset.append((misspelled_word, word))
        #print(dataset)
    return dataset

def prepare_data(dataset):
    misspelled_words, correct_words = zip(*dataset)
    tokenizer = Tokenizer()
    tokenizer.fit_on_texts(misspelled_words + correct_words)
    misspelled_seq = tokenizer.texts_to_sequences(misspelled_words)
    correct_seq = tokenizer.texts_to_sequences(correct_words)
    misspelled_seq = pad_sequences(misspelled_seq)
    correct_seq = pad_sequences(correct_seq)
    return misspelled_seq, correct_seq, tokenizer

def build_lstm_model(vocab_size, max_length):
    model = Sequential()
    model.add(Embedding(vocab_size, 64, input_length=max_length))
    model.add(LSTM(64))
    model.add(Dense(vocab_size, activation='softmax'))
    model.compile(loss='sparse_categorical_crossentropy', optimizer='adam')
    return model

dataset = generate_dataset(correct_words)
misspelled_seq, correct_seq, tokenizer = prepare_data(dataset)  # Store the tokenizer

vocab_size = len(tokenizer.word_index) + 1
max_length = misspelled_seq.shape[1]

model = build_lstm_model(vocab_size, max_length)
model.fit(misspelled_seq, correct_seq, epochs=5, batch_size=64)

def word_correction(input_word, tokenizer):
    input_seq = pad_sequences(tokenizer.texts_to_sequences([input_word]), maxlen=max_length)
    predicted_seq = model.predict(input_seq).argmax(axis=-1)[0]
    suggested_word = tokenizer.index_word[predicted_seq]
    return suggested_word

# Example usage:
while True:
    user_input = input("Enter a misspelled word (or 'q' to quit): ").lower()
    if user_input == 'q':
        break
    suggested_word = word_correction(user_input, tokenizer)
    print(f"Suggested correction for '{user_input}': {suggested_word}")
