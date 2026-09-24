# Exercice 15 - votre première clé

J’ai fabriqué une clé de signature hors du dépôt Git, comme demandé.

## Commande employée

```bash
keytool -genkeypair -v \
  -keystore /Users/levizoonyaba/.keys/ani-4087-release.jks \
  -keyalg RSA \
  -keysize 2048 \
  -validity 10000 \
  -alias ani4087 \
  -dname "CN=LEVIZOO, OU=ANI, O=ANI, L=Montreal, ST=QC, C=CA"
```

La commande complète réelle a aussi utilisé `-storepass` et `-keypass`, mais je ne les mets pas ici pour ne pas exposer le mot de passe.

## Emplacement de la clé

La clé a été créée ici :

```text
/Users/levizoonyaba/.keys/ani-4087-release.jks
```

## Mot de passe

Le mot de passe est rangé ailleurs que dans le dépôt, dans ce fichier :

```text
/Users/levizoonyaba/.secrets/ani-4087-signing-pass.txt
```

C’est bien hors du dépôt Git, donc il n’apparaît pas dans le projet public.
