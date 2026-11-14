from instrumentation import Instrumentation

ins = Instrumentation.Instance()


def doSomeStuff():
    ins.startTiming("doSomeStuff()")
    print("Hello there!")
    ins.stopTiming("doSomeStuff()")


def main():
    ins.activate(True)
    ins.startTiming("main")
    ins.startTiming("loop")
    for i in range(5):
        doSomeStuff()
    ins.stopTiming("loop")
    ins.comment("this is an example of a comment!")
    ins.stopTiming("main")
    ins.dump("logs/example.log")


main()
