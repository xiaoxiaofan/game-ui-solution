package org.wuban.event;

import javax.swing.JFrame;


public class WakeUpEvent2 implements EventObject{

	public WakeUpEvent2() {
		
	}

	@Override
	public void process() {
		System.out.println("if you don't wake up,you will late");
	}

}
