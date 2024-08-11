b = 2 
div = 2 
flag = 0 
while b < 10000:
    flag = 1 
    div = 2 
    while div < b / 2 + 1 :
        if (int)( b / div ) * div == b :
            flag = 0 
        div = div + 1
    if flag :
        print(b)
    b = b + 1 

