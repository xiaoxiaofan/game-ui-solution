package org.wuban.event;

public class DateEvent2 implements EventObject {

	public DateEvent2() {
		
	}
	
	@Override
	public void process() {
		System.out.println("you have a date,this is very importment.");
	}

}
