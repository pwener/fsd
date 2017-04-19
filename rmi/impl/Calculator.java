import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calculator extends Remote {
	/**
	 * Realizes sum operation
	 * 
	 * @param firstNumber
	 * @param secondNumber
	 * @return
	 */
	Float add(Float firstNumber, Float secondNumber) throws RemoteException;

	/**
	 * Realizes subtraction operation
	 * 
	 * @param firstNumber
	 * @param secondNumber
	 * @return
	 */
	Float sub(Float firstNumber, Float secondNumber) throws RemoteException;

	/**
	 * Realizes division operation
	 * 
	 * @param firstNumber
	 * @param secondNumber
	 * @return
	 */
	Float div(Float firstNumber, Float secondNumber) throws RemoteException;

	/**
	 * Realizes multiply operation
	 * 
	 * @param firstNumber
	 * @param secondNumber
	 * @return
	 */
	Float mul(Float firstNumber, Float secondNumber) throws RemoteException;
}
