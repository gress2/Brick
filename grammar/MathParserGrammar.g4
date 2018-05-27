parser grammar MathParserGrammar;

options {tokenVocab = MathLexerGrammar;}

math: expr END;
expr: expr (MULTIPLY|DIVIDE) expr
	|	expr (PLUS|MINUS) expr
	|	INT
	| ID
	| OPENPAREN expr CLOSEPAREN
	| OPENBRACK expr CLOSEBRACK
	;
