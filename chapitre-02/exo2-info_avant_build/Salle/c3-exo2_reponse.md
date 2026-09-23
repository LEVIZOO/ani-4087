# Ce que ça m'apprend que le fichier ne disait pas

Mon fichier `Salle.jenga` dit juste ça pour mon projet :

```python
with project("MaSalle"):
    consoleapp()
    language("C++")
    location("MaSalle")
    files(["src/**.cpp", "include/**.hpp"])
```

Il ne parle pas de :

- Où se trouve le workspace sur mon disque (`Location`, `Entry file`)
- Quels compilateurs sont installés sur ma machine (`Available Toolchains` : `host-apple-clang` et `clang-mingw`, que je n'ai jamais déclarés)
- Que les tests ne sont pas activés (`Test: No`)
- Que le daemon n'est pas lancé (`Daemon: Not running`)

Donc le fichier `.jenga` dit ce que je veux construire, et `jenga info` me dit ce que Jenga voit et sait réellement sur ma machine à cet instant.