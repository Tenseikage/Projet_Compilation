import os
import subprocess
from typing import Tuple


def compile() -> None:
    """
    Cette fonction crée l'exécutable du
    projet pour la mise en place des tests
    """
    if os.path.exists("bin/tpcas") == False:
        command = "make"
        subprocess.run(command,stderr = subprocess.PIPE,check=False)
        #print(result)

        

def test_tpc_files(good: int, bad: int) -> Tuple[int, int]:
    """
    Cette fonction teste les 50 fichiers de chaque
    dossier(good et syn-err) et renvoie un tuple qui contient le nombre de tests
    réussis
    """
    directory1 = os.listdir("test/good")
    directory2 = os.listdir("test/syn-err")
    print("             ERREURS DE TESTS")
    print("---------------------------------------------------")
    for k in range(len(directory1)):
        command1 = ["./bin/tpcas -n", "<", "./test/good/" + directory1[k]]
        command2 = ["./bin/tpcas -n", "<", "./test/syn-err/" + directory2[k]]
        result1 = subprocess.run(" ".join(command1), shell=True, stderr=subprocess.PIPE, check=False)
        result2 = subprocess.run(" ".join(command2), shell=True, stderr=subprocess.PIPE, check=False)
        if (result1.returncode == 0) : good+=1
        else:
            print(f"test/good/{directory1[k]}: Expecté 0 comme sortie, trouvé {result1.returncode}") 
        if (result2.returncode == 1) :bad+=1
        else:
            print(f"test/good/{directory2[k]}: Expecté 1 comme sortie, trouvé {result2.returncode}") 
        
        
    
    return (good,bad)

def final_report(tuple: tuple) -> None:
    print("---------------------------------------------------")
    print("  RAPPORT TESTS ANALYSEUR LEXICAL ET SYNTAXIQUE")
    good = tuple[0]/50*100
    bad =  tuple[1]/50*100
    print(f"Taux de réussite des tests du dossier test/good : {good:.2f}%")
    print(f"Taux de réussite des tests du dossier test/syn-err : {bad:.2f}%")
    final_rate = (good + bad) / 2
    print(f"Taux final : {final_rate:.2f}%")
    print("---------------------------------------------------")
    
    

if __name__ == "__main__":
    compile()
    tuple = test_tpc_files(0,0)
    final_report(tuple)
    
    