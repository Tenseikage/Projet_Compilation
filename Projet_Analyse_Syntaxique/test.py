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

        

def test_tpc_files(good: int, syn_err :int, sem_err: int,warn: int) -> Tuple[int, int]:
    """
    Cette fonction teste les 50 fichiers de chaque
    dossier(good et syn-err) et renvoie un tuple qui contient le nombre de tests
    réussis
    """
    directory1 = os.listdir("test/good")
    directory2 = os.listdir("test/syn-err")
    directory3 = os.listdir("test/warn")
    directory4 = os.listdir("test/sem-err")
    print("---------------------------------------------------")
    print("             SORTIE DE TESTS test/good")
    print("---------------------------------------------------")
    for k in range(len(directory1)):
        command1 = ["./bin/tpcc", "<", "./test/good/" + directory1[k]]
        result1 = subprocess.run(" ".join(command1), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        print(f"test/good/{directory1[k]}: \n{result1.stderr.decode()}")
        
    print("---------------------------------------------------")
    print("             ERREURS DE TESTS test/good")
    print("---------------------------------------------------")
    for k in range(len(directory1)):
        command1 = ["./bin/tpcc", "<", "./test/good/" + directory1[k]]
        result1 = subprocess.run(" ".join(command1), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        if (result1.returncode == 0) : good+=1
        else:
            print(f"test/good/{directory1[k]}: Expecté 0 comme sortie, trouvé {result1.returncode}") 

    print("---------------------------------------------------")
    print("             SORTIE DE TESTS test/syn-err")
    print("---------------------------------------------------")
    for k in range(len(directory2)):
        command2 = ["./bin/tpcc", "<", "./test/syn-err/" + directory2[k]]
        result2 = subprocess.run(" ".join(command2), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        print(f"test/syn-err/{directory2[k]}: \n{result2.stderr.decode()}")
    print("---------------------------------------------------")
    print("             ERREURS DE TESTS test/syn-err")
    print("---------------------------------------------------")
    for k in range(len(directory2)):
        command2 = ["./bin/tpcc", "<", "./test/syn-err/" + directory2[k]]
        result2 = subprocess.run(" ".join(command2), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        if (result2.returncode == 1) : syn_err+=1
        else:
            print(f"test/syn-err/{directory2[k]}: Expecté 1 comme sortie, trouvé {result2.returncode}")
    print("---------------------------------------------------")
    print("             SORTIE DE TESTS test/warn")
    print("---------------------------------------------------")
    for k in range(len(directory3)):
        command3 = ["./bin/tpcc", "<", "./test/warn/" + directory3[k]]
        result3 = subprocess.run(" ".join(command3), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        print(f"test/warn/{directory3[k]}: \n{result3.stderr.decode()}")
    print("---------------------------------------------------")
    print("             ERREURS DE TESTS test/warn")
    print("---------------------------------------------------")
    for k in range(len(directory3)):
        command3 = ["./bin/tpcc", "<", "./test/warn/" + directory3[k]]
        result3 = subprocess.run(" ".join(command3), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        if (result3.returncode == 0) : warn+=1
        else:
            print(f"test/warn/{directory3[k]}: Expecté 0 comme sortie, trouvé {result3.returncode}")

    print("---------------------------------------------------")
    print("             SORTIE DE TESTS test/sem-err")
    print("---------------------------------------------------")
    for k in range(len(directory4)):
        command4 = ["./bin/tpcc", "<", "./test/sem-err/" + directory4[k]]
        result4 = subprocess.run(" ".join(command4), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        print(f"test/sem-err/{directory4[k]}: \n{result4.stderr.decode()}")
    print("---------------------------------------------------")
    print("             ERREURS DE TESTS test/sem-err")
    print("---------------------------------------------------")
    for k in range(len(directory4)):
        command4 = ["./bin/tpcc", "<", "./test/sem-err/" + directory4[k]]
        result4 = subprocess.run(" ".join(command4), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
        if (result4.returncode == 2) : sem_err+=1
        else:
            print(f"test/sem-err/{directory4[k]}: Expecté 2 comme sortie, trouvé {result4.returncode}")
    
    return (good,syn_err,sem_err,warn)

def final_report(tuple: tuple) -> None:
    directory1 = os.listdir("test/good")
    directory2 = os.listdir("test/syn-err")
    directory3 = os.listdir("test/warn")
    directory4 = os.listdir("test/sem-err")
    print("---------------------------------------------------")
    print("  RAPPORT TESTS COMPILATEUR")
    good = tuple[0]/len(directory1)*100
    syn_err =  tuple[1]/len(directory2)*100
    sem_err = tuple[2]/len(directory4)*100
    warn = tuple[3]/len(directory3)*100
    print(f"Taux de réussite des tests du dossier test/good : {good:.2f}%")
    print(f"Taux de réussite des tests du dossier test/syn-err : {syn_err:.2f}%")
    print(f"Taux de réussite des tests du dossier test/sem-err : {sem_err:.2f}%")
    print(f"Taux de réussite des tests du dossier test/warn : {warn:.2f}%")
    final_rate = (good + syn_err + sem_err + warn) / 4
    print(f"Taux final : {final_rate:.2f}%")
    print("---------------------------------------------------")
    
    

if __name__ == "__main__":
    compile()
    tuple = test_tpc_files(0,0,0,0)
    final_report(tuple)
    
    