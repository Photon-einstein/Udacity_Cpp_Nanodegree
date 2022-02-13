#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */
template <typename T>
MessageQueue<T>::MessageQueue()
{
}

template <typename T>
MessageQueue<T>::~MessageQueue()
{
}
 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics.
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> uLock(_mtx);
    std::cout<<"MessageQueue received with thread id " << std::this_thread::get_id() << std::endl;
    _condition.wait(uLock, [this] {return !_msgQueue.empty();}); // unique lock is passed to condition variable
    /* when it returns then msgQueue is no longer empty */
    T msg = std::move(_queue.back()); // get newest message
    _queue.clear(); // empty buffer from old messages
    _msgQueue.pop_front();
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock:guard<std::mutex> uLock(_mtx);
    /* add new message to the queue using move semantics in the background */
    _queue.emplace_back(msg);
    /* notify one thread after insertion */
    _conditionVariable.notify_one();
    return;
}

/* Implementation of class "TrafficLight" */
 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight()
{
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop
    // runs and repeatedly calls the receive function on the message queue.
    // Once it receives TrafficLightPhase::green, the method returns.
    TrafficLightPhase light;
    while (true) {
        light = _msgQueue.receive();
        if (light == TrafficLightPhase::green) {
            return;
        }
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this);
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles
    // and toggles the current phase of the traffic light between red and green and sends an update method
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds.
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.
    std::chrono::time_point<std::chrono::system_clock> lastCycleTime = std::chrono::system_clock::now();
    std::random_device dev;
    std::mt19937 rng(dev);
    std::uniform_int_distribution<std::mt19937::result_type> dist(4000, 6000); // uniform distribution in range [4000, 6000]
    int nCycleDurationVal = dist(rng);
    while (true) {
        /* include a small sleep time of 1 ms before deciding action to do next */
        std::this_thread::sleep_for(std::chrono::miliseconds(1));
        /* measure the duration of the time since the last cycle */
        int deltaTime = std::chrono::duration_cast<std::chrono::miliseconds>(std::chrono::system:clock::now() - lastCycleTime).count();
        /* check if it is time to count as another cycle, in the range of 4-6 s */
        if (deltaTime >= nCycleDurationVal) {
            /* get the next value of duration for the next cycle */
            nCycleDurationVal = dist(rng);
            /* update the lastCycleTime */
            lastCycleTime = std::chrono::system_clock::now();
            /* flip the current phase of the light */
            _currentPhase = (_currentPhase == TrafficLightPhase::green) ? TrafficLightPhase::red : TrafficLightPhase::green;
            // FP 4 : push each new TrafficLightPahse into _msgQueue qith move semantics */
            _msgQueue.push_back(std::move(_currentPhase));

        }
    }
    return;
}
