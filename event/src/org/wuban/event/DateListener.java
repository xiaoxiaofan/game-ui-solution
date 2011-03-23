package org.wuban.event;

public class DateListener implements EventListener {

	private EventObject event;
	
	public DateListener(EventObject ev) {
		this.event = ev;
	}
	@Override
	public void performed() {
	    this.event.process();
	}

}
