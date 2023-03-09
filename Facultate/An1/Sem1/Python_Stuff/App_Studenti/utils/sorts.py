#modulul pentru functii de sortare

def sort_selection(sir, key = lambda x : x, cmp = None, reversed=False):
    #sortare prin selectie
    #returneaza sirul sortat in functie de key si reversed
    if cmp is None:
        def cmp(x,y):
            if key(x) <= key(y):
                return -1
            else: return 1

    for i in range(len(sir)):
        min = i
        for j in range(i+1, len(sir)):
            if reversed==False:
                if cmp(sir[min],sir[j]) > 0:
                    min = j
            else:  
                if cmp(sir[min],sir[j]) < 0:
                    min = j
        sir[i], sir[min] = sir[min], sir[i]
    
    return sir

def sort_shake(sir, key = lambda x: x, cmp = None, reversed=False):
    #sortare prin cocktail sort/ shake sort
    #returneaza sirul sortat in functie de key si reversed
    
    if cmp is None:
        def cmp(x,y):
            if key(x) <= key(y):
                return -1
            else: return 1

    swapped = True
    start = 0
    end = len(sir)-1

    while (swapped == True):
        swapped = False
        for i in range(start, end):
            if reversed==False:
                if cmp(sir[i],sir[i + 1]) > 0:
                    sir[i], sir[i + 1] = sir[i + 1], sir[i]
                    swapped = True
            else:
                if cmp(sir[i],sir[i + 1]) < 0:
                    sir[i], sir[i + 1] = sir[i + 1], sir[i]
                    swapped = True

        if (swapped == False):
            break

        swapped = False
        end = end-1

        for i in range(end-1, start-1, -1):
            if reversed==False:
                if cmp(sir[i],sir[i + 1]) > 0:
                    sir[i], sir[i + 1] = sir[i + 1], sir[i]
                    swapped = True
            else:
                if cmp(sir[i],sir[i + 1]) < 0:
                    sir[i], sir[i + 1] = sir[i + 1], sir[i]
                    swapped = True

        start = start + 1
    
    return sir
