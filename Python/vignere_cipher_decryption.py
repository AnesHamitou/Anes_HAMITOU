#This program decrypts a message encrypted using Vignère cipher (without knowing the key) :
#   To decrypt a message, this program tests the decryption with all possible keys, for example if the key has a maximum 
#   length of 5, it begins to decrypt using as key A ..... Z then AA ........ ZZ to AAAAA ........ ZZZZZ
#   then it selects the best decrypted sentence that looks like english   
#   For this, the program uses :
#       -An english dictionary which contains english quadgrams and a Python program that calculates sentence scores according 
#	 to their similarity to English : https://github.com/jameslyons/python_cryptanalysis/blob/master/ngram_score.py 
#   The key here is set to have a maximum size of 10 characters, this can be changed by modifying the 'for' loop at line 92
#   See example file 'vignere_autobreak.txt'

import ngram_score as ns
import numpy as np

fit=ns.ngram_score('english_quadgrams.txt') 

def grid():
        """
        prints Vignère table
        """
        print("    ",end="")
        for i in range(65,91):
                print("%c"%i,end=" ")
        print("")
        print("    ",end="")
        for i in range(65,91):
                print("_",end=" ")
        print("")
        for i in range(65,91):
                print("%c |"%i,end=" ")
                j=i
                while (j<=90):
                        print("%c"%j,end=" ")
                        j +=1
                j=65
                while (j<i):
                        print("%c"%j,end=" ")
                        j +=1
                print("")
        print("")




def encrypt(msg,key,opt=False):
        """
        Vignère encrypt/decrypt
        """
        msg_returned=[0]*(len(msg))
        if opt: #DECRYPT
	        for i in range(len(msg)):
	        	msg_returned[i]=chr(((ord(msg[i])-ord(key[i%len(key)]))%26)+65)
        else: #ENCRYPT
	        for i in range(len(msg)):
	        	msg_returned[i]=chr(((ord(key[i%len(key)])+ord(msg[i])-(2*65))%26)+65)
        return msg_returned

def best_score(mylist,index,msg_encry):
	"""
	This function tests the -index- of -mylist- from A to Z, decrypts using this list 
	and returns the best one (best score)  
	"""
	bestlist=list(mylist)
	init_decrypted=encrypt(msg_encry,''.join(mylist),True)
	best_score_decrypt=fit.score(''.join(init_decrypted))
	for k in range(65,91):
		mylist[index]=chr(k)
		r=encrypt(msg_encry,''.join(mylist),True)
		score_r=fit.score(''.join(r))
		if score_r>best_score_decrypt:
			best_score_decrypt=score_r
			bestlist=list(mylist)
	return bestlist

def autobreak(encrypted_msg):	
	"""
	For each length (n) (1...10) : 
	the function finds the best (key, decrypted message) by testing all possibilities
        
	A....Z
	AA.....ZZ
	AAA.......ZZZ 
        to AAAAAAAAAA.......ZZZZZZZZZZ

	Then it saves the best one (text) in a list -l_max_final_text- and its score in a list -l_max_final_score-

	Using these lists, it prints the best key, the best decrypted message and it's score for each key length.
	"""
	l_tmp_score=[]
	l_tmp_text=[]
	l_max_final_score=[]
	l_max_final_text=[]
	for length in range(1,11): #key length (here, maximum 10 characters)
		for letter in range(65,91):
			l=[chr(letter)]*length
			#To test each time another loop and finds if the key changes
			stable=False 
			while not stable:
				for k in range(length):
					l=list(best_score(l,k,encrypted_msg))
				#The second loop for testing changes
				l2=list(l)
				for k in range(length):
					l2=list(best_score(l2,k,encrypted_msg))
				if l==l2 :
					stable=True
			decrypted_with_the_best_key=''.join(encrypt(encrypted_msg,''.join(l),True))
			score=fit.score(''.join(decrypted_with_the_best_key))
			l_tmp_text.append(l)
			l_tmp_score.append(score)
		max_index=np.argmax(l_tmp_score)
		l_max_final_score.append(l_tmp_score[max_index])
		l_max_final_text.append(l_tmp_text[max_index])
	for i in range(10):#Printing the keys, decrypted messages and scores
		decrypted=''.join(encrypt(encrypted_msg,''.join(l_max_final_text[i]),True))
		print(decrypted,''.join(l_max_final_text[i]),fit.score(''.join(decrypted)))


#TEST
grid()
c=(''.join(encrypt("HELLOEVERYONETHISISANENGLISHSENTENCEANDTHISPROGRAMISWRITTENINPYTHONLANGUAGE","HELLOWORLD")))
print(" 'HELLO EVERYONE THIS IS AN ENGLISH SENTENCE AND THIS PROGRAM IS WRITTEN IN PYTHON LANGUAGE' encrypted using the key 'HELLOWROLD' becomes ->",c)
print("Now we decrypt it")
autobreak(c)
