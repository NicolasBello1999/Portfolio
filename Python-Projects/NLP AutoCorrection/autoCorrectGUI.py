import tkinter as tk # GUI
from tkinter import * # GUI

import string # get the alphabet easily
from pathlib import Path # easier way to access files
from collections import Counter # word analyzation
import textdistance as txdis # edit distance calculations/algorithms such as levenshtein MED and Jaccard Distance
import numpy as np # generally good to have
import pandas as pd
import nltk # download corpus libraries and use other natural language tools
import re

# ML models for us to train
import tensorflow as tf
from tensorflow import keras
from keras.models import Sequential
from keras.layers import Embedding, LSTM, Dense
from sklearn.model_selection import train_test_split

from nltk.corpus import words

nltk.download('punkt')
nltk.download('words')

class autoCorrect:
    # small list/set of correct words for training our model
    correctWords = ['something', 'position', 'apple', 'future', 'helicopter', 'simple', 'feet']

    # this method does live auto correction but is VERY unoptimized due to time constraints // Note: does NOT work for this project
    def dynamicAutoCorrect():
        top = tk.Toplevel()
        top.title('AutoCorrectshion : Dynamic Auto Correct')
        top.geometry("1280x720")

        top.textBox = tk.Text(top, width = 152, height = 32, font=("Times New Roman", 12))
        top.textBox.bind("<KeyRelease>", autoCorrect.checkMisspelling) # each time the user clicks on a key, wordChecker function is called to check if the word is valid
        top.textBox.pack(pady=24)

        buttonFrame = tk.Frame(top)
        buttonFrame.pack()

        buttonClear = tk.Button(buttonFrame, text="Clear Text", command = autoCorrect.clearText(top))
        buttonClear.grid(row = 0, column = 0)
    
    # allows user to type as much as they want and then they are able to click different buttons to activate auto correct features (less performance heavy)
    def staticAutoCorrect(self):
        #self.readCorpus("brown.txt")

        self.top = tk.Toplevel()
        self.top.title('AutoCorrectshion : Static Auto Correct')
        self.top.geometry("1280x720")

        self.textBox = tk.Text(self.top, width = 152, height = 28, font=("Times New Roman", 12))
        self.textBox.pack(side = tk.TOP, padx = 10, pady= 10)

        displayInfo = f"Total unique words loaded from file are {len(self.vocabs)}\nThe most common words are: {self.wordFreq.most_common()[0:5]}"
        something = tk.Label(self.top, text = displayInfo).pack(side = tk.RIGHT, padx=10, pady=10)

        buttonFrame = tk.Frame(self.top)
        buttonFrame.pack(side = tk.BOTTOM, pady = 20)

        #textAreaFrame = tk.Frame(self.top).grid(row = 0, column = 0)

        #buttonClear = tk.Button(buttonFrame, text="Clear Text", command = autoCorrect.clearText(top))
        #buttonClear.grid(row = 0, column = 0)

        buttonCheckWords = tk.Button(buttonFrame, text = "Check Misspelt Words", command = lambda : self.static_CheckMisspelling())
        buttonCheckWords.grid(row = 0, column = 0)

        labelV1 = tk.Label(buttonFrame, text = "Correct By Comparison w/dataset ---> ")
        labelV1.grid(row = 1, column = 0)

        buttonAutoCorrect_v1 = tk.Button(buttonFrame, text = "Auto Correct - v1", command = lambda : self.makeCorrection(1))
        buttonAutoCorrect_v1.grid(row = 1, column = 1)

        labelV2 = tk.Label(buttonFrame, text = "Correct By MED (Minimum Edit Distance) w/dataset ---> ")
        labelV2.grid(row = 2, column = 0)

        buttonAutoCorrect_v2 = tk.Button(buttonFrame, text = "Jaccard Dist. - v2.1", command = lambda : self.makeCorrection(2))
        buttonAutoCorrect_v2.grid(row = 2, column = 1)

        buttonAutoCorrect_v2 = tk.Button(buttonFrame, text = "Levenshtein Dist. - v2.2", command = lambda : self.makeCorrection(3))
        buttonAutoCorrect_v2.grid(row = 2, column = 2)

        labelV3 = tk.Label(buttonFrame, text = "Correct By LSTM Model w/dataset ---> ")
        labelV3.grid(row = 3, column = 0)
        
        buttonAutoCorrect_v3 = tk.Button(buttonFrame, text = "Auto Correct - v3", command = lambda : self.makeCorrection(4))
        buttonAutoCorrect_v3.grid(row = 3, column = 1)


    # constructor that will act as the main menu on start up
    def __init__(self):
        self.misspeltWords = [] # hold list of misspelt words
        self.root = tk.Tk()
        self.root.title('AutoCorrectshion : Main Menu')
        self.root.geometry("400x400")

        self.readCorpus("brown.txt") # load our given text file
        #self.trainModel()
        self.trainingModel()
        
        #frame = tk.Frame(self.root).pack()
        #descFrame = tk.LabelFrame(frame, text = "Program Description")
        #descFrame.grid(row = 0, column = 0)

        #description = tk.Label(descFrame, text = "This program is about NLP...")
        #description.grid(row = 0, column = 0)
        #description.pack()

        dynamicAutoCorrection = tk.Button(self.root, text = "Live Auto Correct", command = autoCorrect.dynamicAutoCorrect).pack()
        staticAutoCorrection = tk.Button(self.root, text = "Static Auto Correct", command = self.staticAutoCorrect).pack()

        #dynamicAutoCorrection.place(relx = 0.5, rely = 0.45, anchor = CENTER)
        #staticAutoCorrection.place(relx = 0.5, rely = 0.55, anchor = CENTER)

        self.root.mainloop() # creates/starts GUI when the Python file begins to run

    def dynamic_CheckMisspelling(self, event):
        #textContent
        if event.char == ' ': # check when user clicks on space
            textContent = self.textBox.get("1.0", tk.END) # get all the words in the textBox 
            tokens = nltk.word_tokenize(textContent) # separate all the words
            for word in tokens: # check if each word is correct or not
                if re.sub(r"[^\w]", "", word.lower()) not in words.words(): # remove special characters and make the word/token lowercase and then check if the word exists
                    pos = textContent.find(word)
                    self.textBox.tag_add(word, f"1.{pos}", f"1.{pos + len(word)}")
                    self.textBox.tag_config(word, foreground = "red")
            print(tokens)

    #@staticmethod
    def static_CheckMisspelling(self):
        for tag in self.textBox.tag_names():
            self.textBox.tag_delete(tag)

        textContent = self.textBox.get("1.0", tk.END) # get all the words in the textBox 
        tokens = nltk.word_tokenize(textContent) # separate all the words
        for word in tokens: # check if each word is correct or not
            curWord = re.sub(r"[^\w]", "", word.lower()) # remove special characters and make the word/token lowercase and then check if the word exists
            if curWord not in words.words():
                pos = textContent.find(curWord)
                self.textBox.tag_add(curWord, f"1.{pos}", f"1.{pos + len(curWord)}")
                self.textBox.tag_config(curWord, foreground = "red") # make the word red to show that its misspelled/misspelt
                self.misspeltWords.append(curWord) # save misspelt words into a list to later use them
        print(tokens) # prints the words its detecting onto the console

    def makeCorrection(self, version):
        top = tk.Toplevel()
        top.title('Possible Word Corrections')
        top.geometry("350x350")

        #scrollBar = tk.Scrollbar(top, orient=tk.VERTICAL)
        #scrollBar.grid(row=0, column=1, sticky="ns")

        #canvas = tk.Canvas(top, width=350, height=350, scrollregion=(0, 0, 300, 350))
        #canvas.grid(row=0, column=0, sticky="nsew")

        #scrollBar.config(command=canvas.yview)
        #canvas.config(yscrollcommand=scrollBar.set)

        # Place widgets inside the canvas
        #frame = tk.Frame(canvas)
        #canvas.create_window((0, 0), window=frame, anchor='nw')
        #frame.bind("<Configure>", lambda : self.on_canvas_configure(canvas))

        if version == 1: # 
            for wrong_word in self.misspeltWords:
                possibleWords = self.oneCharEdits(wrong_word) or self.twoCharEdits(wrong_word) or [wrong_word]
                validWords = [i for i in possibleWords if i in self.vocabs]
                results = sorted([(j, self.wordProbability[j]) for j in validWords], key = lambda tup: tup[1], reverse = True)

                displayResults = tk.Label(top, text = results).pack()
        elif version == 2: # using Jaccard Distance from our list of misspelt words
            for wrong_word in self.misspeltWords:
                sim = [1 - (txdis.Jaccard(qval = 2).distance(x, wrong_word)) for x in self.wordFreq.keys()]
                dataFrame = pd.DataFrame.from_dict(self.WordProbs_v2, orient = 'index').reset_index()
                dataFrame = dataFrame.rename(columns = {'index' : 'Word', 0:'Prob'})
                dataFrame['Similarity'] = sim
                output = dataFrame.sort_values(['Similarity', 'Prob'], ascending = False).head()

                displayResults = tk.Label(top, text = output).pack()
        elif version == 3: # using Levenshtein Distance from our list of misspelt words
            pass
        elif version == 4: # the ML part of the project, using a LSTM model which is a special class of RNN architecture used for Machine Translation
            for wrong_word in self.misspeltWords:
                correct = self.wordCorrection_Model(wrong_word)
                #accuracy = self.calculateAccuracy(3)
                #accText = 'Accuracy = ' + accuracy + '\n'

                displayResults = tk.Label(top, text = correct).pack()
                #displayAccuracy = tk.Label(top, text = accText).pack()

    
    # read the file and use it as part of our untrained data set for our model or distance algorithms
    def readCorpus(self, filename):
        try:
            self.WordProbs_v2 = {}
            filepath = Path(__file__).parent / filename
            with open(filepath, "r") as file:
                lines = file.readlines()
                wordsList = []

                for word in lines:
                    wordsList += re.findall(r'\w+', word.lower())
            
            self.vocabs = set(wordsList)
            self.wordFreq = Counter(wordsList)
            self.totalAmount = float(sum(self.wordFreq.values()))
            self.wordProbability = {word: self.wordFreq[word] / self.totalAmount for word in self.vocabs}

            for i in self.wordFreq.keys():
                self.WordProbs_v2[i] = self.wordFreq[i] / self.totalAmount

            print(f"Total unique words in file ({filename}) are {len(self.vocabs)}")
            print(f"The most common words are: {self.wordFreq.most_common()[0:10]}")
        except Exception as e:
            print(f"ERROR: {e}")

    # take in a word and create a variety of misspellings of said word in order to create a dataset
    # I implemented this function because I couldn't find a good training dataset that wasn't big enough or one that wasn't behind a paywall (I have to pay for the corpus file)
    def oneCharEdits(self, word):
        alphabet = string.ascii_lowercase # self implied
        wordSplits = [(word[:x], word[x:]) for x in range(len(word) + 1)] # split the word in every possible combination
        wordDeletes = [l + r[1:] for l,r in wordSplits if r] # delete a letter from the word
        wordSwaps = [l + r[1] + r[0] + r[2:] for l,r in wordSplits if len(r) > 1]
        wordReplaces = [l + c + r[1:] for l,r in wordSplits if r for c in alphabet]
        wordInserts = [l + c + r for l,r in wordSplits for c in alphabet] # insert a new letter into the word

        return set(wordDeletes + wordSwaps + wordReplaces + wordInserts) # return a tuple
    
    # create a list a incorrect words by doing two character edits of the correct version of the word, this is to create our dataset
    def twoCharEdits(self, word):
        return set(w2 for w1 in self.oneCharEdits(word) for w2 in self.oneCharEdits(w1))
    
    # AKA minimal edit distance (MED)
    def levenshteinDistance(self, word, misspeltWord):
        return txdis.levenshtein.normalized_similarity(word, misspeltWord)

    def prepareData(self, dataset): # prepare the data for our model
        misspelled_words, correct_words = zip(*dataset)
        self.tokenizer = keras.preprocessing.text.Tokenizer()
        self.tokenizer.fit_on_texts(misspelled_words + correct_words)
        misspelled_seq = self.tokenizer.texts_to_sequences(misspelled_words)
        correct_seq = self.tokenizer.texts_to_sequences(correct_words)
        misspelled_seq = keras.preprocessing.sequence.pad_sequences(misspelled_seq)
        correct_seq = keras.preprocessing.sequence.pad_sequences(correct_seq)
        return misspelled_seq, correct_seq, self.tokenizer
    
    def build_lstm_model(self, vocabSize, maxLength):
        model = Sequential()
        model.add(Embedding(vocabSize, 64, input_length = maxLength))
        model.add(LSTM(64))
        model.add(Dense(vocabSize, activation='softmax'))
        model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
        return model
    
    def generateDataset(self, correctWords):
        dataset = []
        for word in correctWords:
            misspellings = list(self.oneCharEdits(word))  # convert set to list
            for misspelled_word in misspellings:
                dataset.append((misspelled_word, word))
        return dataset
    
    def trainingModel(self):
        print("Training LSTM Model...")

        dataset = self.generateDataset(self.correctWords)
        misspelledSeq, correctSeq, tokenizer = self.prepareData(dataset)

        vocabSize = len(tokenizer.word_index) + 1
        self.maxLength = misspelledSeq.shape[1]

        misspelledSeq_train, misspelledSeq_val, correctSeq_train, correctSeq_val = train_test_split(
        misspelledSeq, correctSeq, test_size=0.2, random_state=42)

        # LSTM model processing dataset parameters (how long it will take to process training dataset)
        epochSize = 10
        batchSize = 1

        self.model = self.build_lstm_model(vocabSize, self.maxLength)
        #self.model.fit(misspelledSeq, correctSeq, epochs = epochSize, batch_size = batchSize)
        self.model.fit(misspelledSeq_train, correctSeq_train, epochs = epochSize, batch_size = batchSize,
                   validation_data = (misspelledSeq_val, correctSeq_val))

        #accuracy = self.calculateAccuracy(k=5)
        #print(f"Model accuracy: {accuracy:.2f}%")

    def wordCorrection_Model(self, input_word):
        inputSeq = keras.preprocessing.sequence.pad_sequences(self.tokenizer.texts_to_sequences([input_word]), maxlen = self.maxLength)
        predicted_seq = self.model.predict(inputSeq).argmax(axis = -1)[0]
        suggested_word = self.tokenizer.index_word[predicted_seq]
        return suggested_word
    
    def calculateAccuracy(self, k):
        correctSuggestions = 0
        total_words = len(self.correctWords)

        for word in self.correctWords:
            misspellings = list(self.oneCharEdits(word))
            suggestions = [self.wordCorrection_Model(misspelled_word) for misspelled_word in misspellings]
            if word in suggestions[:k]:  # consider correct if any of the top 'k' suggestions matches the correct word
                correctSuggestions += 1

        accuracy = (correctSuggestions / total_words) * 100
        return accuracy

app = autoCorrect()
