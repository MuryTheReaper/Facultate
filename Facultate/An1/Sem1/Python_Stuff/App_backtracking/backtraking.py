#Problema 7 (cea cu paranteze)
#{(x1,x2,x3,...,xn) | xi din {-1, 1}, i din {1,2,3,...,n},Vxi,x1+x2+x3+...+xi>=0 si x1+x2+...+xn=0 }

def print_solutie(sol:list):
    for i in range(0,len(sol)):
        if sol[i]==0:
            print("(", end="")
        else:
            print(")", end="")
    print()
        
def testare_solutie(sol:list):
    nrD=0
    nrI=0
    for i in range(0,len(sol)):
        if sol[i]==0:
            nrD+=1
        else:
            nrI+=1
    if nrI>nrD:
        return 0
    elif nrI==nrD:
        return 2
    return 1
    

def generate_paranteze_recursiv(sol:list,dim:int):
    if len(sol)==dim and testare_solutie(sol)==2:
        print_solutie(sol)
        return
    sol.append(0)
    for i in range(0,2):
        sol[-1]=i
        if testare_solutie(sol)!=0 and len(sol)<=dim:
            generate_paranteze_recursiv(sol,dim)
    sol.pop()

def generate_paranteze_iterativ(sol:list,dim:int):
    sol.append(-1)
    while len(sol)>0:
        ok=0
        while ok==0 and sol[-1]<1:
            sol[-1]=sol[-1]+1
            ok=testare_solutie(sol)

        if ok!=0 and len(sol)<=dim:
            if ok==2 and len(sol)==dim:
                print_solutie(sol)
            sol.append(-1)
        else:
            sol.pop()
    

print("RECURSIV: ")
generate_paranteze_recursiv([],8)
print("ITERATIV: ")
generate_paranteze_iterativ([],8)
print("Done")
