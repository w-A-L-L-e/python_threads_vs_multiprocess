all: threads_with_cpp 

threads_with_cpp: threads.cpp
	$(CXX) $(CXXFLAGS) threads.cpp -o $@ -lpthread

clean:
	@rm -vf threads_with_cpp

