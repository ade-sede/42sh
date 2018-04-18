# 42sh
A 42 school project. 
A bash style shell with some features from Oh my Zsh.
Made with 4 persons. A bash style shell with some features from Oh my Zsh.
The project follow the C Norme of 42 school. if you dont see any 'for' or 'case', or have to witness some awful code, dont be surprised, blame the Norme !
[42 - Norme](https://www.fichier-pdf.fr/2013/07/19/norme42/preview/page/1/)

### DISCLAIMER
The following list of features is not accurate, some have been removed from the project because unstable, while some do not figure in the list.
The features presented in the following document should be here and enable relatively experienced user to use this shell without too much discomfort.
[42 - 42sh Subject](http://cdn.intra.42.fr/pdf/pdf/183/42sh.fr.pdf)


## Line editing

Keys|Functions|
:-:|:--
<kbd>Opt</kbd>+<kbd>v</kbd><br><kbd>Opt</kbd>+<kbd>c</kbd><br><kbd>Opt</kbd>+<kbd>p</kbd><br>|Enter visual mode<br>Copy<br>Paste
<kbd>Opt</kbd>+<kbd>&#x2190;</kbd><br><kbd>Opt</kbd>+<kbd>&#x2192;</kbd>|Move per words.
<kbd>Opt</kbd>+<kbd>&#x2191;</kbd><br><kbd>Opt</kbd>+<kbd>&#x2193;</kbd>|Move per line.

## History

Keys|Functions|
:-:|:--
<kbd>&#x2191;</kbd><br><kbd>&#x2193;</kbd>|Browse the history.
<kbd>Ctrl</kbd>+<kbd>R</kbd>|Back Search.
`!!`|Retype the last command.
`!n`|Retype the `n`(numerical value) command from the begin of history.
`!-n`|Retype the `-n`(numerical value) command from the last command.
`!name`|Search for a command beginning with `name`.
`!?name`|Search for a command which contain `name`.

## Autocompletion

Autocompletion works with binary, path and env variable.
Output is colored upon type.
Using arrows to navigate is supported.
Autorefreshing with a new input from the user: modification of the list of possibility.

Commands|Functions|
:-:|:--
`$> l[tab]`|Search for binary.
`$> ls s[tab]`|Search for path/files.
`$> $[tab]`|Search for variables in `env`.
`$> [a-b]{1,2}*[tab]`|Search file matching pattern.

## Globbing
Posix globbing see [Pattern Matching Notation](http://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap02.html#tag_18_13_01)

Pattern|Behavior|
:-:|:--
`*`|Everything.
`?`|Single char.
`[a-z]`|Match range from `a` to `z`.
`[!a-z]` `[^a-z]`|Exclude range from `a` to `z`.

## Job Control

Commands|Functions|
:-:|:--
`jobs`|List all the current running jobs.
`fg`|Bring the most recent process to foreground.
`fg n`|Bring the specified jobs to foreground where `n` is the numerical value of the process found in `jobs`.
<kbd>Ctrl</kbd>+<kbd>C</kbd>|Terminate/Kill current foreground process.
<kbd>Ctrl</kbd>+<kbd>Z</kbd>|Suspend/Stop current foreground process.

## Variable Expansion

During execution, the shell perform various expansion as specified by [POSIX](http://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap02.html#tag_18_06_02). Our Shell do in order:

commands | Exemple | Functions
:-:|:-:|:--
• Brace Expansion: `a{d,c,b}e`|	`a{d,c,b}e` | 	Expansion of expressions within braces.
• Tilde Expansion: |	`~` |	Expansion of the ~ character.
• Shell Parameter Expansion| `$PATH`, `${PATH}`, `${#PATH}` |expands local and environement variable.
• Command Substitution |	`$(ls)`, \`echo a\`|  	Using the output of a command as an argument.
• Word Splitting|	$> IFS=a; var=baba echo $var => b b  |	the result of the three expansions above are splitted into token using IFS variable.
• Filename Expansion |	`*`, `[a-z]`, `[!a-z]` | 	 match file with shell regex.
• Quote Removal |	$>echo "lol" => lol  |	remove quotes and backslash as needed.

## Grammar
### Tokens
Bellow the tokens of the POSIX Grammar which can take many litteral forms. In the exemple le token is in ' '.

Tokens|Exemple|
:-:|:--
WORD| ls './srcs'
ASSIGNMENT_WORD| 'a=b' ;
NAME| for 'foo' in bar; do ls; done
NEWLINE| ls '\n' ls
IO_NUMBER| ls ./srcs '2'&>1

### Rules
Bellow the Backus Naur form of the POSIX Grammar which we parse and execute.

Symbol|Components|
:-:|:--
complete_commands| complete_commands newline_list complete_command<br/>                                complete_command
complete_command | list separator_op<br/> list
list             | list separator_op and_or<br/>                   and_or
and_or           |                         pipeline<br/> and_or '&&' linebreak pipeline<br/> and_or '||'  linebreak pipeline
pipeline         |      pipe_sequence<br/> '!' pipe_sequence
pipe_sequence    |                             command<br/> pipe_sequence '<br/>' linebreak command
command          | simple_command<br/> compound_command<br/> compound_command redirect_list<br/> function_definition
compound_command | brace_group<br/> subshell<br/> for_clause<br/> case_clause<br/> if_clause<br/> while_clause<br/> until_clause
subshell         | '(' compound_list ')'
compound_list    | linebreak term<br/> linebreak term separator
term             | term separator and_or<br/>                and_or
for_clause       | 'for' name                                      do_group<br/> 'for' name                       sequential_sep do_group<br/> 'for' name linebreak in          sequential_sep do_group<br/> 'for' name linebreak in wordlist sequential_sep do_group
name             | NAME                     
in               | 'in'                       
wordlist         | wordlist WORD<br/>          WORD
case_clause      | 'case' WORD linebreak in linebreak case_list    'esac'<br/> 'case' WORD linebreak in linebreak case_list_ns 'esac'<br/> 'case' WORD linebreak in linebreak              'esac'
case_list_ns     | case_list case_item_ns<br/>           case_item_ns
case_list        | case_list case_item<br/>           case_item
case_item_ns     |     pattern ')' linebreak<br/>     pattern ')' compound_list<br/> '(' pattern ')' linebreak<br/> '(' pattern ')' compound_list
case_item        |     pattern ')' linebreak     ';;' linebreak<br/>     pattern ')' compound_list ';;' linebreak<br/> '(' pattern ')' linebreak     ';;' linebreak<br/> '(' pattern ')' compound_list ';;' linebreak
pattern          |             WORD         
if_clause        | 'if' compound_list 'then' compound_list else_part 'fi'<br/> 'if' compound_list 'then' compound_list           'fi'
else_part        | 'elif' compound_list 'then' compound_list<br/> 'elif' compound_list 'then' compound_list else_part<br/> 'else' compound_list
while_clause     | 'while' compound_list do_group
until_clause     | 'until' compound_list do_group
function_definition | fname '(' ')' linebreak function_body
function_body    | compound_command                
fname            | NAME                            
brace_group      | '{' compound_list '}'
do_group         | 'do' compound_list 'do'ne           
simple_command   | cmd_prefix cmd_word cmd_suffix<br/> cmd_prefix cmd_word<br/> cmd_prefix<br/> cmd_name cmd_suffix<br/> cmd_name
cmd_name         | WORD                   
cmd_word         | WORD                   
cmd_prefix       |            io_redirect<br/> cmd_prefix io_redirect<br/>            ASSIGNMENT_WORD<br/> cmd_prefix ASSIGNMENT_WORD
cmd_suffix       |            io_redirect<br/> cmd_suffix io_redirect<br/>            WORD<br/> cmd_suffix WORD
redirect_list    |               io_redirect<br/> redirect_list io_redirect
io_redirect      |           io_file<br/> IO_NUMBER io_file<br/>           io_here<br/> IO_NUMBER io_here
io_file          | '<'       filename<br/> '<&'   filename<br/> '>'       filename<br/> '>&'  filename<br/> '>>'    filename<br/> '<>' filename<br/> '>|'   filename
filename         | WORD                      
io_here          | '<<'     here_end<br/> '<<-' here_end
here_end         | WORD                      
newline_list     |              NEWLINE<br/> newline_list NEWLINE
linebreak        | newline_list<br/> 
separator_op     | '&'
separator        | separator_op linebreak<br/> newline_list<br/> newline_list

## Exemples
This code of the factorial function works fine in our shell.
```sh
factorial()
{
  if [ "$1" -gt "1" ]; then
    i=$(( $1 - 1))
    j=$(factorial $i)
    k=$(($1 * $j))
    echo $k
  else
    echo 1
  fi
}   
```
You can find more exemple of what our shell handles in the Exemple directory.

## Authors
* **COMBEY Vincent** - [vcombey](https://github.com/vcombey)
* **DE SEDE Adrien** - [ade-sede](https://github.com/ade-sede)
* **EDDAOUDI Said** - [github]()
* **DUMOULIN Thibaut** - [github]()
