import nltk
from nltk.corpus import wordnet as wn

nltk.download('wordnet') # our dictionary

# checks if the word exists within the human English language/lexicon
def is_valid_word(word: str) -> bool: 
    return word.lower() in wn.words()

# checks to see if the new word from user starts with a letter from the previous words last letter, hence a snake game
def check_letters(previous_word: str, new_word: str) -> bool:
    return new_word[0].lower() == previous_word[-1].lower()