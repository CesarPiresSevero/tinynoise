# Script to check repeating sequences

# start='fe52\nf9c\n116f\n51bd\n831b\n9970\nf058\n25bf\n9384\n8758\n'
start='fe52\nf9c\n116f\n51bd\n831b\n'

# prev=['Hey']*10
prev=['Hey']*5
with open('log.txt') as f:
    for i,line in enumerate(f):
        prev[0:-1] = prev[1:-1]
        prev.append(line)
        txt = ''.join(prev)
#         print(prev)
        if(txt.count(start)):
            print("I FOUND ONE")
#         input()
        

