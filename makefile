OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : test-tnode test-bst test-gst test-rbt test-main

test : test-tnode test-bst test-gst test-rbt test-main
	./test-tnode
	./test-bst
	./test-gst
	./test-rbt
	./trees -r t-0-1.corpus t-0-1.commands

valgrind : test-tnode test-bst test-gst test-rbt test-main
	valgrind test-tnode
	valgrind test-bst
	valgrind test-gst
	valgrind test-rbt
	valgrind trees -r t-0-8.corpus t-0-8.commands

clean : 
	rm -f $(OBJS) test-bst test-rbt test-gst test-tnode trees

test-bst : $(OBJS)
	gcc $(LOPTS) cda.c queue.c integer.c tnode.c bst.c bst-0-4.c -o test-bst -lm

test-rbt : $(OBJS)
	gcc $(LOPTS) cda.c queue.c tnode.c integer.c gst.c rbt.c bst.c rbt-0-4.c -o test-rbt -lm

test-gst : $(OBJS)
	gcc $(LOPTS) tnode.c bst.c cda.c queue.c integer.c gst.c gst-0-4.c -o test-gst -lm

test-tnode : $(OBJS)
	gcc $(LOPTS) integer.c queue.c cda.c tnode.c bst.c tnode-0-0.c -o test-tnode -lm

test-main: $(OBJS)
	gcc $(LOPTS) string.c scanner.c cda.c queue.c bst.c tnode.c gst.c rbt.c main.c -o trees -lm
