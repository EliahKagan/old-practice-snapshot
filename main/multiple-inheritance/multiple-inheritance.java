interface Foo {
    default public void f()
    {
        System.out.println("Foo.f()");
    }
}

interface Bar extends Foo {
    default public void f()
    {
        System.out.println("Bar.f()");
    }
}

final class FooBar implements Foo, Bar {
    
}
