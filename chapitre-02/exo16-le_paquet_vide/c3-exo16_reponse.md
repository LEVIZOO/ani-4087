# Exercice 16 - le paquet vide

J’ai empaqueter mon petit programme, meme si il ne fait que montrer une couleur. J’ai aussi le signe pour que ca ressemble a un vrai paquet Android.

## Le paquet

Le paquet cree est la :

```text
/Users/levizoonyaba/ani-4087/chapitre-02/exo16-le_paquet_vide/AppColor.apk
```

Taille du paquet :

```text
2.8K
```

## La commande utilise pour signer

Je n’ai pas mis le mot de passe, comme demande :

```bash
jarsigner \
  -keystore /Users/levizoonyaba/.keys/ani-4087-release.jks \
  -signedjar /Users/levizoonyaba/ani-4087/chapitre-02/exo16-le_paquet_vide/AppColor.apk \
  /tmp/AppColor-unsigned.jar \
  ani4087
```

Le mot de passe est range ailleurs que dans le depot, ici :

```text
/Users/levizoonyaba/.secrets/ani-4087-signing-pass.txt
```

## Ce que le paquet contient

J’ai regarde l’interieur du fichier .apk avec unzip, et il contient ceci :

```text
Archive:  /Users/levizoonyaba/ani-4087/chapitre-02/exo16-le_paquet_vide/AppColor.apk
  Length      Date    Time    Name
---------  ---------- -----   ----
      339  09-24-2026 20:36   META-INF/MANIFEST.MF
      501  09-24-2026 20:36   META-INF/ANI4087.SF
     1329  09-24-2026 20:36   META-INF/ANI4087.RSA
      547  09-24-2026 20:36   AndroidManifest.xml
      110  09-24-2026 20:36   res/values/strings.xml
       11  09-24-2026 20:36   assets/color.txt
---------                     -------
     2837                     6 files
```

Donc le paquet contient :
- le manifest Android
- les fichiers de signature
- une ressource texte pour le nom de l’app
- un fichier `assets/color.txt` avec la couleur de fond

C’est un paquet tres simple, mais il est bien signe et il est bien empaqueter.

## Conclusion

Le but de l’exercice est de montrer qu’un .apk est juste une archive, qu’on peut le signer, et qu’on peut l’ouvrir avec des outils d’archive. J’ai bien fait ca, et le paquet est dans le dossier de l’exercice.
