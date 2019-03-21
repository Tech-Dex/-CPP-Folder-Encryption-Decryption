# Folder-Encryption-Decryption
A program that encrypt content of a Folder - Images and Text Documents and after that can decrypt.


### Requirements
  * OpenCV 4.0.0 
  * Baisc Library
  
### Files Allowed 
  * '.txt'
  * '.jpg'
  * '.png'


#### How to use
```
g++ {nameCompiledFile} -o {randomFileName} `pkg-config --cflags --libs opencv`
./randomName
Example
g++ main.cpp -o encrypt-decrypt `pkg-config --cflags --libs opencv`
./encrypt-decrypt

First time when you will use ./encrypt-decrypt will encrypt folder files.
Second time when you will use ./encrypt-decrypt will decrypt folder files.
```

## General Idea about this project
 * I learnt to use OpenCV core functions
 * Practicing bitwise operations
