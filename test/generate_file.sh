#!/bin/bash

# -----------------------------------------------------------------------------
# Génère une large série de fichiers pour tester get_next_line_bonus
# Contient différents cas limites : vide, sans \n, lignes longues, etc.
# -----------------------------------------------------------------------------

echo "🛠️  Génération des fichiers de test..."

# Nettoyage préalable pour éviter les doublons
rm -f f*.txt

# 10 fichiers vides
for i in $(seq 1 10); do
    > "f_empty_$i.txt"
done

# 10 fichiers sans retour à la ligne final
for i in $(seq 1 10); do
    echo -n "ligne unique sans retour" > "f_no_nl_$i.txt"
done

# 10 fichiers avec 100 lignes
for i in $(seq 1 10); do
    for j in $(seq 1 100); do
        echo "ligne $j du fichier $i" >> "f_long_$i.txt"
    done
done

# 10 fichiers contenant uniquement des \n
for i in $(seq 1 10); do
    printf "\n\n\n\n\n" > "f_empty_lines_$i.txt"
done

# 10 fichiers avec une ligne très longue (> BUFFER_SIZE)
for i in $(seq 1 10); do
    head -c 5000 < /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 5000 | head -n 1 > "f_huge_line_$i.txt"
done

echo "✅ Fichiers générés : $(ls f*.txt | wc -l)"
