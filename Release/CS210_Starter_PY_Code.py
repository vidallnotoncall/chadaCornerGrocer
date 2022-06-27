import re
import string



def createFreqDictionary():
    dailyPurchases = {}
    #read the presented file
    f = open("CS210_Project_Three_Input_File.txt")
    contents = f.readlines()
    #create an array of purchased items
    NewContents = []
    #remove new line and change each item to lowercase for easier matching
    for element in contents:
        NewContents.append(element.strip().lower())
    #create the dictonary
    for item in NewContents:
        #if the item isnt in the dictionary add it
        if (item not in dailyPurchases):
            dailyPurchases[item] = 1
        #if the item is in the dicitonary increase its count by 1
        dailyPurchases[item] = dailyPurchases[item] + 1
    return dailyPurchases;

def PrintFrequencyAll():
    FrequencyList = createFreqDictionary()
    #print the full dictionary
    for i in FrequencyList:
        print (i, FrequencyList[i])
    
    
def PrintFrequencyOne(item):
    FrequencyList = createFreqDictionary()
    #check to see if item is in dictionary
    if FrequencyList.get(item) is not None:
        #print one item from the dictionary
        print (item, FrequencyList[item])
    else: 
        #if item does not exist inform user
        print ("This item does not exist")
 
    return 1;

#not used. make histogram with python
#def createHistogram():
#    i = 1
#    histoCount = ""
#    FrequencyList = createFreqDictionary()

#    for item in FrequencyList:
#        while (i <= FrequencyList[item]):
#            histoCount += "*"
#            i += 1
#        else:
#            print(item, histoCount)
#            histoCount = ""
#           i = 1

def createFreqFile():
    FrequencyList = createFreqDictionary()
    #create frequency.dat file and open it for writing
    f = open("frequency.dat", "w")
    #until end of dictionary write file onto frequency.dat
    for i in FrequencyList:
        f.write(i)
        f.write(" ")
        #write doesnt accept int so convert to string
        f.write(str(FrequencyList[i]))
        f.write("\n")
    #close the file
    f.close()