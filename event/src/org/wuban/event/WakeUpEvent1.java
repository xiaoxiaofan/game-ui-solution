package org.wuban.event;




public class WakeUpEvent1 implements EventObject{

	public WakeUpEvent1() {
		
	}

	@Override
	public void process() {
		System.out.println("you should wake up.");
	}

}
