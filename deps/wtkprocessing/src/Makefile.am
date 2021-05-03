AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x
lib_LTLIBRARIES = libwtkprocessing.la

libwtkprocessing_includedir=$(includedir)/wtkprocessing

libwtkprocessing_include_HEADERS =	proc_utilities.hpp \
				     	Filter.hpp \
				     	Car.hpp Dc.hpp Laplacian.hpp \
				      	Window.hpp \
				    	Hann.hpp Hamming.hpp Flattop.hpp Blackman.hpp Rectangular.hpp\
				    	Method.hpp \
				    	Pwelch.hpp Periodogram.hpp\
				    	Classifier.hpp \
				    	Gaussian.hpp Qda.hpp\
				    	GaussianCimo.hpp \
				    	Algorithm.hpp \
				    	Exponential.hpp Rejector.hpp \
				    	Buffer.hpp \
				    	RingBuffer.hpp \
				    	SimpleBuffer.hpp \
				    	Csp.hpp BankCsp.hpp \
				    	Entropy.hpp \
				        ExponentialPd.hpp \
				        Windsor.hpp \
				        Normalize.hpp \
				        BLDA.hpp \
					SWLDA.hpp \
					Biquad.hpp \
					Butterworth.hpp \
					ButterFilter.hpp \
					Padding.hpp \
					Hilbert.hpp \
					Envelope.hpp
			    
libwtkprocessing_la_SOURCES = 		proc_utilities.hpp \
					proc_utilities.cpp \
			      		Filter.hpp \
					Filter.cpp \
					Car.hpp Dc.hpp Laplacian.hpp \
					Car.cpp Dc.cpp Laplacian.cpp \
					Window.hpp \
					Window.cpp \
					Hann.hpp Hamming.hpp Flattop.hpp Blackman.hpp Rectangular.hpp\
					Hann.cpp Hamming.cpp Flattop.cpp Blackman.cpp Rectangular.cpp\
					Method.hpp \
					Method.cpp \
					Pwelch.hpp Peridogram.hpp\
					Pwelch.cpp Periodogram.cpp\
					Classifier.hpp \
					Classifier.cpp \
					Gaussian.hpp Qda.hpp \
					Gaussian.cpp Qda.cpp \
					GaussianCimo.cpp \
					Algorithm.hpp \
					Algorithm.cpp \
					Exponential.hpp Rejector.hpp \
					Exponential.cpp Rejector.cpp \
					Buffer.hpp \
					Buffer.cpp \
					RingBuffer.hpp \
					RingBuffer.cpp \
					SimpleBuffer.hpp \
					SimpleBuffer.cpp \
					Csp.hpp BankCsp.hpp \
					Csp.cpp BankCsp.cpp \
					Entropy.hpp Entropy.cpp \
					ExponentialPd.hpp ExponentialPd.cpp \
					Windsor.hpp \
					Windsor.cpp \
					Normalize.hpp \
					Normalize.cpp \
					BLDA.hpp \
					BLDA.cpp \
					SWLDA.hpp \
					SWLDA.cpp \
					Biquad.hpp \
					Biquad.cpp \
					Butterworth.hpp \
					Butterworth.cpp \
					ButterFilter.hpp \
					ButterFilter.cpp \
					Padding.hpp \
					Padding.cpp \
					Hilbert.hpp \
					Hilbert.cpp \
					Envelope.hpp \
					Envelope.cpp

		      
libwtkprocessing_la_LDFLAGS = $(AM_CFLAGS) \
		      -version-info $(CURRENT):$(REVISION):$(AGE) \
		      -release $(RELEASE)

libwtkprocessing_la_LIBADD   = -lfftw3 -ltinyxml2 -lwtkcore
libwtkprocessing_la_CPPFLAGS = -I/usr/include/eigen3

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wtkprocessing.pc
