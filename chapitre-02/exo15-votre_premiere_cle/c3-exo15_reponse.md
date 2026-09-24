# Exercice 15 - votre premiere cle

J’ai fabriquer une cle de signature en dehors du depot Git, comme il est demande. J’ai pas mis la cle dans le projet, ni dans le repo. C’est pas dans le dossier GitHub, c’est ailleurs sur mon Mac.

## La commande que j’ai utilise

```bash
keytool -genkeypair -v \
  -keystore /Users/levizoonyaba/.keys/ani-4087-release.jks \
  -keyalg RSA \
  -keysize 2048 \
  -validity 10000 \
  -alias ani4087 \
  -dname "CN=LEVIZOO, OU=ANI, O=ANI, L=Montreal, ST=QC, C=CA"
```

J’ai pas mis le mot de passe dans cette commande, parce que c’est secret. La vraie commande utilisait aussi les options `-storepass` et `-keypass`, mais je ne les ecris pas ici pour ne pas montrer le mot de passe.

## Ou est la cle ?

La cle de signature a ete cree ici :

```text
/Users/levizoonyaba/.keys/ani-4087-release.jks
```

Donc elle est dehors du depot, dans un dossier perso, pas dans le projet.

## Ou j’ai range le mot de passe ?

Le mot de passe est range dans un autre endroit, en dehors du repo :

```text
/Users/levizoonyaba/.secrets/ani-4087-signing-pass.txt
```

C’est un fichier secret, et il n’est pas dans le dossier du git. Donc on est bien conforme au sujet : la clé et le mot de passe ne sont pas dans le depot.

## Conclusion

J’ai bien fait une cle de signature, elle est hors du projets Git, et le mot de passe est aussi hors du depot. J’ai mis la commande sans le mot de passe, et j’ai dit ou le mot de passe est range.
