import java.util.Objects;

public class Person implements Comparable<Person> {
	private String firstName;
	private String lastName;
	private int age;

	public Person(String firstName, String lastName, int age) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.age = age;
	}

	public String getFirstName() {
		return firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public int getAge() {
		return age;
	}

	@Override
	public String toString() {
		return firstName + ", " + lastName + ", " + age;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Person person = (Person) o;
		return age == person.age && Objects.equals(firstName, person.firstName) && Objects.equals(lastName, person.lastName);
	}

	@Override
	public int compareTo(Person other) {
		return Integer.compare(this.age, other.getAge());
	}

	@Override
	public int hashCode() {
		return super.hashCode();
	}
}
