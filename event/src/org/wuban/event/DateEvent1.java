package org.wuban.event;

public class DateEvent1 implements EventObject {

	public DateEvent1() {
		
	}
	
	@Override
	public void process() {
		System.out.println("you have a date");
	}

}
