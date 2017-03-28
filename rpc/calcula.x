struct operandos {
	int x;
	int y;
};

program PROG {
	version VERSAO {
		int add(operandos) = 1;
		int sub(operandos) = 2;
		int mul(operandos) = 3;
		int div(operandos) = 4;
	} = 1;
} = 10;
