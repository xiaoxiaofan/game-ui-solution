package org.wuban.event;

public class WakeUpEvent3 implements EventObject{

	public WakeUpEvent3() {
		
	}

	@Override
	public void process() {
		System.out.println("this is you last chance.");
	}

}
