
import java.util.*;

import java.util.LinkedList;
import java.util.Queue;

	public class AgeQueue {
	    private Queue<Person> queue;

	    public AgeQueue() {
	        this.queue = new LinkedList<>();
	    }

	    public void addPerson(Person person) {
	        queue.add(person);
	    }

	    public Person removePerson() {
	        Person oldest = null;
	        int oldestAge = -1;

	        for (Person p : queue) {
	            if (oldest == null || p.getAge() > oldestAge) {
	                oldest = p;
	                oldestAge = p.getAge();
	            }
	        }

	        queue.remove(oldest);
	        return oldest;
	    }

	    public boolean isEmpty() {
	        return queue.isEmpty();
	    }
	}

 