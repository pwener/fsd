import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/**
 * We have one calculator server
 */
public class Server implements Calculator {

	public static void main(String[] args) {
		try {
			Server obj = new Server();
			Calculator stub = (Calculator) UnicastRemoteObject.exportObject(obj, 0);

			Registry registry = LocateRegistry.getRegistry();
			registry.bind("Calculator", stub);

			System.out.println("Server ready");
		} catch (Exception e) {
			System.err.println("Server exception: " + e.toString());
			e.printStackTrace();
		}
	}

	@Override
	public Float add(Float firstNumber, Float secondNumber) {
		return firstNumber + secondNumber;
	}

	@Override
	public Float sub(Float firstNumber, Float secondNumber) {
		return firstNumber - secondNumber;
	}

	@Override
	public Float div(Float firstNumber, Float secondNumber) {
		return firstNumber / secondNumber;
	}

	@Override
	public Float mul(Float firstNumber, Float secondNumber) {
		return firstNumber * secondNumber;
	}

}
