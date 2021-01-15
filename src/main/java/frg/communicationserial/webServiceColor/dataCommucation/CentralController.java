package frg.communicationserial.webServiceColor.dataCommucation;

import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import jssc.SerialPort;
import jssc.SerialPortException;

@RestController
public class CentralController {

	static String[] arr = null;
	static SerialPort sport = null;

	public static void iniciarSerial() throws SerialPortException {
		try {
			sport = new SerialPort("/dev/ttyUSB2");

			sport.openPort();

			sport.setParams(1200, 8, 1, 0);

		} catch (SerialPortException ex) {
			if (sport.isOpened()) {
				sport.closePort();
			}
			System.out.println(ex);
		}
	}
	
	@RequestMapping("/read")
	public String readSerial() throws SerialPortException {
		return sport.readString();
	}

	@RequestMapping("/off")
	public void off() throws SerialPortException {
		sport.writeString("OFF");
	}
	
	@RequestMapping("/clr/{r}/{g}/{b}")
	public void setColor(@PathVariable int r,@PathVariable int g,@PathVariable int b) throws SerialPortException{
		sport.writeString("CLR|" + r + "|" + g + "|" + b);
	}
	
	@RequestMapping("/clt/{temp}")
	public void setColorTemperature(@PathVariable String temp) throws SerialPortException{
		sport.writeString("CLT|" + temp);
	}
	
	@RequestMapping("/fio/{r}/{g}/{b}")
	public void setFadeInFadeOut(@PathVariable int r,@PathVariable int g,@PathVariable int b) throws SerialPortException{
		sport.writeString("FIO|" + r + "|" + g + "|" + b);
	}
	
	@RequestMapping("/str/{r}/{g}/{b}/{count}/{flashDelay}/{pause}")
	public void setStrobe(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int count,@PathVariable int flashDelay,@PathVariable int pause) throws SerialPortException, InterruptedException {
		sport.writeString("STR|" + r + "|" + g + "|" + b + "|" + count + "|" + flashDelay + "|" + pause);
	}
	
	@RequestMapping("/cyl/{r}/{g}/{b}/{tamFaixa}/{speed}/{retspeed}")
	public void setCylon(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int tamFaixa,@PathVariable int speed,@PathVariable int retspeed) throws SerialPortException, InterruptedException {
		sport.writeString("CYL|" + r + "|" + g + "|" + b + "|" + tamFaixa + "|" + speed + "|" + retspeed);
	}
	
	@RequestMapping("/ktt/{r}/{g}/{b}/{tamFaixa}/{speed}/{retspeed}")
	public void setKITT(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int tamFaixa,@PathVariable int speed,@PathVariable int retspeed) throws SerialPortException, InterruptedException {		
		sport.writeString("KTT|" + r + "|" + g + "|" + b + "|" + tamFaixa + "|" + speed + "|" + retspeed);
	}
	
	@RequestMapping("/coo/{r}/{g}/{b}/{tamFaixa}/{speed}/{retspeed}")
	public void setCenterToOutside(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int tamFaixa,@PathVariable int speed,@PathVariable int retspeed) throws SerialPortException, InterruptedException {
		sport.writeString("COO|" + r + "|" + g + "|" + b + "|" + tamFaixa + "|" + speed + "|" + retspeed);
	}
	
	@RequestMapping("/spk/{r}/{g}/{b}/{speed}/{retspeed}")
	public void setSparkle(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int speed,@PathVariable int retspeed) throws SerialPortException, InterruptedException {
		sport.writeString("SPK|" + r + "|" + g + "|" + b + "|" + speed + "|" + retspeed);
	}
	
	@RequestMapping("/snp/{r}/{g}/{b}/{spark}/{retspeed}")
	public void setSnowSparkle(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int spark,@PathVariable int retspeed) throws SerialPortException, InterruptedException {
		sport.writeString("SNP|" + r + "|" + g + "|" + b + "|" + spark + "|" + retspeed);
	}
	
	@RequestMapping("/rlt/{r}/{g}/{b}/{speed}/{wavespeed}")
	public void setRunningLights(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int speed,@PathVariable int wavespeed) throws SerialPortException, InterruptedException {
		sport.writeString("RLT|" + r + "|" + g + "|" + b + "|" + speed + "|" + wavespeed);
	}
	
	@RequestMapping("/cwp/{r}/{g}/{b}/{speed}")
	public void setColorWipe(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int speed) throws SerialPortException, InterruptedException {
		sport.writeString("CWP|" + r + "|" + g + "|" + b + "|" + speed);
	}
	
	@RequestMapping("/thc/{r}/{g}/{b}/{speed}")
	public void setTheaterChase(@PathVariable int r,@PathVariable int g,@PathVariable int b,@PathVariable int speed) throws SerialPortException, InterruptedException {
		sport.writeString("THC|" + r + "|" + g + "|" + b + "|" + speed);
	}
	
	@RequestMapping("/rbw")
	public void setRainbow() throws SerialPortException, InterruptedException {
		sport.writeString("RBW");
	}
	
	@RequestMapping("/rbg")
	public void setGlitterRainbow() throws SerialPortException, InterruptedException {
		sport.writeString("RBG");
	}
	
	@RequestMapping("/cnf")
	public void setConfetti() throws SerialPortException, InterruptedException {
		sport.writeString("CNF");
	}
	
	@RequestMapping("/sin")
	public void setSinelon() throws SerialPortException, InterruptedException {
		sport.writeString("SIN");
	}
	
	@RequestMapping("/bpm")
	public void setBPM() throws SerialPortException, InterruptedException {
		sport.writeString("BPM");
	}
	
	@RequestMapping("/jug")
	public void setJugger() throws SerialPortException, InterruptedException {
		sport.writeString("JUG");
	}
	
	@RequestMapping("/plt/{palette}/{blend}")
	public void setPalette(@PathVariable String palette, @PathVariable String blend) throws SerialPortException{
		sport.writeString("PLT|" + palette + "|" + blend);
	}
	
	/*@RequestMapping("/snk")
	public void setSnake() throws SerialPortException, InterruptedException {
		pauseForNextEffect();
		sport.writeString("SNK");
	}
	
	@RequestMapping("/pac")
	public void setPacMan() throws SerialPortException, InterruptedException {
		pauseForNextEffect();
		sport.writeString("PAC");
	}*/

}
