"""Un compilateur d'expressions arithmétiques vers de l'assembleur.
L'évaluation des expressions se fait via la pile, comme vu en cours
de compilation."""

import re

# Entrée utilisateur (défaut : False)
# Si True, demande une expression à l'utilisateur.
ENTREE_UTILISATEUR = False
# L'exemple, à modifier à loisir
MON_EXEMPLE = "70-5*2-10+4*5"
# Le fichier où écrire l'assembleur
NOM_FICHIER = "anonymous.asm"


def tokenise(text):
    """Un lexer très basique qui renvoie une liste de tokens,
    chaque token étant une str.
    Paramètres :
    - text (str) : l'expression à lexer"""
    return list(re.findall(r"\+|-|\*|/|[0-9]+", text))


# Dans la suite, on représente les arbres (binaires) comme des tuples
# (nom_du_nœud, valeur_du_nœud, fils_gauche, fils_droit),
# où l'arbre vide est `None`.
# Ce modèle d'arbre est légèrement modifié par rapport à celui vu en TD
# pour coller au plus près de votre projet.


# On fait un parser à la main pour l'occasion.
# Comme vous le voyez, c'est un peu fastidieux !
# D'autant qu'il faut lire de droite à gauche
# pour faciliter la gestion de la priorité des opérateurs.
# C'est un peu de la magie noire, il n'est pas nécessaire de comprendre
# cette fonction (même si c'est intéressant).
# La fonction intéressante est `genere_asm_expression`.

def parse_tokens(tokens, i, fils_droit):
    """Renvoie l'arbre syntaxique d'une expression lexée,
    donnée comme une liste de tokens.
    Paramètres :
    tokens (str list) : la liste de tokens
    i (int) : l'indice à partir duquel on parse (de droite à gauche)
    fils_droit (arbre) : le fils droit courant, où on accumule les produits
                         et divisions.

    Le parser doit lire de droite à gauche pour gérer correctement le "-"
    sans trop s'embêter.
    """
    # On a terminé
    if i < 0:
        return fils_droit
    # Sinon, on regarde le token courant
    token = tokens[i]
    match token:
        case '+' | '-':
            # On peut mettre le fils droit courant
            return ('ADDSUB', token,
                    parse_tokens(tokens, i-1, None),
                    fils_droit)
        # On doit continuer de construire le fils droit
        # en accumulant les produits et diviseurs
        case '*' | '/':
            fils_droit = ('DIVSTAR', token, None, fils_droit)
            return parse_tokens(tokens, i-1, fils_droit)
        # On traite une valeur numérique
        case num_str:
            # On assume de provoquer une erreur
            # si l'expression est mal formée
            num = int(num_str)
            feuille = ('NUM', num, None, None)
            match fils_droit:
                case None:
                    # Pas de fils droit : on a simplement une valeur numérique
                    fils_droit = feuille
                    # Sinon, on rajoute la valeur numérique en fils gauche
                case (nom, valeur, None, fils_droit):
                    fils_droit = (nom, valeur, feuille, fils_droit)
                case default:
                    # On soulève une erreur si notre arbre est mal formé
                    raise ValueError(f"Bizarre : {default}")
            return parse_tokens(tokens, i-1, fils_droit)


def parse_expression(text):
    """Renvoie l'arbre syntaxique d'une expression donnée sous forme de texte.
    Paramètres :
    - text (str) : l'expression"""
    tokens = tokenise(text)
    return parse_tokens(tokens, len(tokens)-1, None)


# La fonction intéressante est ici :
def genere_asm_expression(arbre, fichier):
    """Génère le code assembleur pour l'expression donnée,
    dans le fichier donné.
    Paramètres :
    - arbre (arbre) : l'arbre syntaxique de l'expression
    - fichier (file) : le fichier où écrire (on le suppose déjà ouvert)
    """
    match arbre:
        # On a une constante numérique
        case ('NUM', constante, None, None):
            fichier.write(f"push {constante}\n")
        # On a un operateur (par exemple une soustraction)
        case (nom, operateur, fils_gauche, fils_droit):
            genere_asm_expression(fils_gauche, fichier)
            genere_asm_expression(fils_droit, fichier)
            fichier.write("pop rcx\n")
            fichier.write("pop rax\n")
            # On va chercher le nom correspondant en assembleur
            # (cf plus bas)
            nom_op_asm = op_asm(nom, operateur)
            fichier.write(f"{nom_op_asm} rax, rcx\n")
            fichier.write("push rax\n")
        # On n'a pas implémenté les autres cas
        case default:
            raise ValueError(
                f"Quelque chose cloche dans votre arbre: {default}")


def op_asm(nom, operateur):
    """Renvoie le nom de l'opérateur donné en assembleur.
    Paramètres :
    - nom (str) : le nom du noeud dans l'arbre syntaxique
    - operateur (str) : l'opérateur"""
    match (nom, operateur):
        case ("ADDSUB", '+'):
            return "add"
        case ("ADDSUB", '-'):
            return "sub"
        case ("DIVSTAR", "*"):
            return "imul"
        # Flemme d'implémenter la division
        case default:
            raise ValueError(f"Cas non implémenté : {default}")


def ecrit_debut(fichier):
    """Écrit le préambule de l'assembleur dans le fichier donné.
    Paramètres :
    - fichier (file) : le fichier où écrire (on le suppose déjà ouvert)
    """
    fichier.write("global _start\n")
    fichier.write("section .text\n")
    fichier.write("_start:\n")


def ecrit_fin(fichier):
    """Écrit la fin de l'assembleur pour que le programme renvoie la valeur
    au sommet de la pile comme code d'erreur dans le fichier donné.
    Paramètres :
    - fichier (file) : le fichier où écrire (on le suppose déjà ouvert)
    """
    # On récupère la valeur de l'expression qui est au sommet de la pile
    # Ce sera la valeur de retour du programme
    # Donc la valeur d'échec du Make
    fichier.write("pop rdi\n")
    # rax = 60 signifie "exit" pour syscall
    fichier.write("mov rax, 60\n")
    fichier.write("syscall\n")


def genere_asm(arbre, nom_fichier):
    """Génère le code assembleur à partir d'un arbre syntaxique
    dans le fichier au chemin donné.
    Paramètres :
    - arbre (arbre) : l'arbre syntaxique
    - nom_fichier (str) : le chemin d'accès du fichier
    """
    with open(nom_fichier, 'w', encoding="utf-8") as fichier:
        ecrit_debut(fichier)
        genere_asm_expression(arbre, fichier)
        ecrit_fin(fichier)


def main():
    # On récupère notre exemple
    if ENTREE_UTILISATEUR:
        texte = input("Entrez une expression arithmétique : ")
    else:
        texte = MON_EXEMPLE
    arbre = parse_expression(texte)
    genere_asm(arbre, NOM_FICHIER)


if __name__ == "__main__":
    main()
