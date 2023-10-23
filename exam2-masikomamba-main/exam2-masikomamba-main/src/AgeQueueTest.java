import org.junit.Test;

import static org.junit.Assert.*;

public class AgeQueueTest {

    @Test
    public void testEmptyQueue() {
        AgeQueue queue = new AgeQueue();
        assertTrue(queue.isEmpty());
    }

    @Test
    public void testSinglePerson() {
        AgeQueue queue = new AgeQueue();
        queue.addPerson(new Person("John", "Doe", 50));
        assertFalse(queue.isEmpty());
        assertEquals(new Person("John", "Doe", 50), queue.removePerson());
        assertTrue(queue.isEmpty());
    }

    @Test
    public void testMultiplePersonsSameAge() {
        AgeQueue queue = new AgeQueue();
        queue.addPerson(new Person("John", "Doe", 50));
        queue.addPerson(new Person("Jane", "Doe", 50));
        assertFalse(queue.isEmpty());
        assertEquals(new Person("John", "Doe", 50), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Jane", "Doe", 50), queue.removePerson());
        assertTrue(queue.isEmpty());
    }

    @Test
    public void testMultiplePersonsDifferentAges() {
        AgeQueue queue = new AgeQueue();
        queue.addPerson(new Person("John", "Doe", 50));
        queue.addPerson(new Person("Jane", "Doe", 60));
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Jane", "Doe", 60), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("John", "Doe", 50), queue.removePerson());
        assertTrue(queue.isEmpty());
    }

    @Test
    public void testMultiplePersonsSameAgeInFIFO() {
        AgeQueue queue = new AgeQueue();
        queue.addPerson(new Person("John", "Doe", 50));
        queue.addPerson(new Person("Jane", "Doe", 50));
        queue.addPerson(new Person("Alice", "Smith", 50));
        assertFalse(queue.isEmpty());
        assertEquals(new Person("John", "Doe", 50), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Jane", "Doe", 50), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Alice", "Smith", 50), queue.removePerson());
        assertTrue(queue.isEmpty());
    }

    @Test
    public void testMultiplePersonsSameAgeAndDifferentAgesInFIFO() {
        AgeQueue queue = new AgeQueue();
        queue.addPerson(new Person("John", "Doe", 50));
        queue.addPerson(new Person("Jane", "Doe", 60));
        queue.addPerson(new Person("Alice", "Smith", 50));
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Jane", "Doe", 60), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("John", "Doe", 50), queue.removePerson());
        assertFalse(queue.isEmpty());
        assertEquals(new Person("Alice", "Smith", 50), queue.removePerson());
        assertTrue(queue.isEmpty());
    }

}
