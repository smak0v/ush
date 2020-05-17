# USH

## Content

- [Description](#description)
- [How to use](#how-to-use)
- [Implemented functionality](#implemented-functionality)
- [Additional functionality](#additional-functionality)
- [Developers](#developers)
- [License]($license)

## Description

Implementation of basic command-line interpreter (based on ```zsh``` and
```bash```), using the C programming language.

## How to use

### Compilation:

```
make
./ush
```

### Reinstalliation:

```
make reinstall
./ush
```

### Uninstalliation:

```
make uninstall
```

## Implemented functionality

### A set of builtins without any flags

- ```export```;
- ```unset```;
- ```local```;
- ```exit```;
- ```bye```;
- ```history```;
- ```return```;
- ```true```;
- ```false```;
- ```jobs```;
- ```fg``` without any arguments and with ```%n```, ```%str```, ```%+```,
```%-```, ```n```, ```str```, ```+```, ```-``` arguments.

### A set of builtins with flags

- ```env``` with next flags:
    - ```-i```;
    - ```-P```;
    - ```-u```.

- ```cd``` with next flags:
    - ```-s```;
    - ```-P```;
    - ```-```.

- ```pwd``` with next flags:
    - ```-L```;
    - ```-P```.

- ```which``` with next flags:
    - ```-a```;
    - ```-s```.

- ```echo``` with next flags:
    - ```-n```;
    - ```-e```;
    - ```-E```.

### Signals namaging

- ```CTRL+D```;
- ```CTRL+C```;
- ```CTRL+Z```.

### Characters escaping

Next characters can be escaped to be used literally: ```space```, ```'```,
```"```, ```$```, ```(```, ```)```, ```\```, \`, ```{```, ```}```.

### Tilde expansions

Tilde expansions ```~``` with the followinf tilde-prefixes:

- ```~```;
- ```~/dir_name```;
- ```username/dir_name```;
- ```~+/dir_name```;
- ```~-/dir_name```.

### Parameter expansions

- only basic form - ```${parameter}```.

### Command substitutions of next forms

- \`command\`
- $(command)

Nested command substitutions also supported.

## Additional functionality

- support of pipes ```|```;
- support of logical operators ```&&``` and ```||```;
- job control system (only for foregraund jobs and processes);
- command history using ```Arrow``` keys;
- command editing, cursor motion using ```Arrow``` keys;
- prompt customization using ```ALT+1``` combination;
- the ```;``` command line separator;
- errors management;
- user rnvironment management.

## Developers

- [Sergey Makov](https://github.com/smak0v)

- [Yulia Bondarenko](https://github.com/kali-y23)

- [Alexander Piskun](https://github.com/alejinjer)

## License

Collision is an open-sourced software licensed under the
[MIT license](LICENSE.md).
