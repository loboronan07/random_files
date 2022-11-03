/* Lab Exercise 3

*/

import java.util.*;

class MyClass {
	boolean set;
	int n;

	MyClass() {
		set = false;
		n = 0;
	}

	synchronized void set(boolean running, int n) {
		set = true;
		if(!running) {

			notify();
			return;
		}

		this.n = n;

		notify();

		try {
			while(set) 
				wait();
		}
		catch(InterruptedException e) {
			System.out.println("Thread Interrupted in Set Method...");
		}
	}

	synchronized void put(boolean running) {
		set = false;
		if(!running) {
			notify();
			return;
		}

		System.out.println("Recieved " + n + " for n...");

		notify();

		try {
			while(!set) 
				wait();
		}
		catch(InterruptedException e) {
			System.out.println("Thread Interrupted in Put Method...");
		}
	}
}

class Producer implements Runnable {
	Thread t;
	MyClass m;

	Producer(MyClass m) {
		t = new Thread(this);
		this.m = m;
		t.start();
	}

	public void run() {
		for(int i=0; i<5; i++)
			m.set(true, i);
		m.set(false, 0);
	}
}

class Consumer implements Runnable {
	Thread t;
	MyClass m;

	Consumer(MyClass m) {
		t = new Thread(this);
		this.m = m;
		t.start();
	}

	public void run() {
		for(int i=0; i<5; i++)
			m.put(true);
		m.put(false);
	}
}

class MyThread implements Runnable {
	Thread t;
	MyClass m;

	MyThread(String name, MyClass m) {
		t = new Thread(this, name);
		this.m = m;
		t.start();
	}

	public void run() {
		if(t.getName().compareTo("P") == 0) {
			for(int i=0; i<5; i++)
				m.set(true, i);
			m.set(false, 0);
		}
		else {
			for(int i=0; i<5; i++)
				m.put(true);
			m.put(false);
		}
	}
}

class exercise3 {
	public static void main(String[] args) {
		MyClass m = new MyClass();
		Producer p = new Producer(m);
		Consumer c = new Consumer(m);

		try {
			p.t.join();
			c.t.join();
		} 
		catch(InterruptedException e) {
			System.out.println("Main Thread Interrupted...");
		}
	}
}