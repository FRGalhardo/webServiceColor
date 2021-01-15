package frg.communicationserial.webServiceColor;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import frg.communicationserial.webServiceColor.dataCommucation.CentralController;
import jssc.SerialPortException;

@SpringBootApplication
public class WebServiceColorApplication {

	public static void main(String[] args) throws SerialPortException {
		
		CentralController cc = new CentralController();
		
		cc.iniciarSerial();
		
		SpringApplication.run(WebServiceColorApplication.class, args);
	}

}
