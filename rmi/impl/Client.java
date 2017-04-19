import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

	private static final String ADD = "+";
	private static final String SUB = "-";
	private static final String DIV = "/";
	private static final String MUL = "*";

	public static void main(String[] args) {
		String host = args[0];

		final Float firstNumber = Float.valueOf(args[1]);
		final Float secondNumber = Float.valueOf(args[3]);

		final String operation = args[2];

		System.out.println("Writes the operation: ");

		try {
			Registry registry = LocateRegistry.getRegistry(host);
			Calculator objectStub = (Calculator) registry.lookup("Calculator");

			Float result = getResultOf(firstNumber, operation, secondNumber, objectStub);

			System.out.println("Result is " + result);
		} catch (Exception e) {
			System.err.println("Client exception: " + e.toString());
			e.printStackTrace();
		} finally {
		}
	}

	private static Float getResultOf(Float firstNumber, String operation, 
			Float secondNumber, Calculator objectStub)
			throws RemoteException {

		Float result = null;

		try {
			if (operation.equals(ADD)) {
				result = objectStub.add(firstNumber, secondNumber);
			} else if (operation.equals(SUB)) {
				result = objectStub.sub(firstNumber, secondNumber);
			} else if (operation.equals(DIV)) {
				result = objectStub.div(firstNumber, secondNumber);
			} else if (operation.equals(MUL)) {
				result = objectStub.mul(firstNumber, secondNumber);
			} else {
				System.err.println("Error, invalid operation");
			}
		} catch (RemoteException e) {
			throw new RemoteException("Remove method fails", e);
		}

		return result;
	}
}
