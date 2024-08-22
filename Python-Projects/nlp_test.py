from nltk.corpus import wordnet as wn
import pandas as pd
import os
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import LabelEncoder
import numpy as np

def get_word_categories(word):
    synsets = wn.synsets(word)
    categories = set()
    for synset in synsets:
        for lemma in synset.lemmas():
            categories.add(lemma.name())
    return list(categories)

def extract_features(word, all_categories):
    features = np.zeros(len(all_categories), dtype=int)
    for category, word_list in data_frame:
        if word in word_list:
            features[label_encoder.transform([category])[0]] = 1
    return features

def classify_word(word):
    features = extract_features(word, all_categories)
    category_idx = classifier.predict([features])[0]
    category = label_encoder.inverse_transform([category_idx])[0]
    return category

# try:
script_dir = os.path.dirname(os.path.abspath(__file__))
data = pd.read_csv(script_dir + "\Ambiguous Word Bank - Sheet1.csv")

data_frame = [(row['Categories'], [word.strip() for word in str(row['List of Words']).split(',')]) for index, row in data.iterrows()]

words = []
categories = []
for category, word_list in data_frame:
    words.extend(word_list)
    categories.extend([category] * len(word_list))

# Extracting all unique categories
all_categories = set([category for category, _ in data_frame])

# Encoding categories
label_encoder = LabelEncoder()
label_encoder.fit(list(all_categories))
encoded_categories = label_encoder.transform(categories)

# Extracting features for all words
X = np.array([extract_features(word, all_categories) for word in words])

# Training the classifier
classifier = RandomForestClassifier()
classifier.fit(X, encoded_categories)

# Test
loop_input: bool = True
while loop_input:
    input_word = input("Enter a word: ")

    if input_word == "exit" or input_word == "quit": 
        loop_input = False
        continue

    result = classify_word(input_word)
    print(f"The word '{input_word}' is classified as '{result}'")
# except Exception as e:
#     print(f"Error opening file, error reads:\n{e}.")
