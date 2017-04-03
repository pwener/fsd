struct operandos {
	int x;
	int y;
};

program PROG {
	version VERSAO {
		int add(operandos) = 1;
		int sub(operandos) = 2;
	} = 100;
} = 11111;
