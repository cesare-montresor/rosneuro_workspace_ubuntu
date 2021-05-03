#ifndef PROC_BLDA_CPP
#define PROC_BLDA_CPP

#include "BLDA.hpp"

namespace wtk {
        namespace proc {


BLDA::BLDA(void) : Classifier(Classifier::AsBLDA) {
        this->_stype 	= "classifier";
        this->_slabel 	= "bayesian-cnbi";

        this->_isset	= false;
}

BLDA::~BLDA(void) {
}


bool BLDA::Setup(std::string filename) {

        hdr_t 	hdr;

        std::ifstream ifs;
        ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        this->_isset = false;

       try {
                ifs.open(filename.c_str(), std::ios::in | std::ios::binary);

                proc_readheader(ifs, &hdr);

                proc_check_string(hdr.type, this->_stype, "The binary file has not type classifier");
                this->config.filename 		= filename;
                this->config.subject		= proc_readstring(ifs);
                this->config.nclasses 		= proc_readbyte(ifs);
                this->config.classlbs 		= proc_readvector<uint32_t>(ifs);
                this->config.nfeatures   	= proc_readbyte(ifs);
                std::cout << "N features " << this->config.nfeatures << std::endl;
                this->config.idchan 		=  proc_readvector<uint32_t>(ifs);
                 std::cout << "Channels " << std::endl;
		for(unsigned int i=0; i< this->config.idchan.size();i++)
			std::cout << this->config.idchan.at(i) << " ";
	        std::cout << std::endl;
                this->config.epochrd            =  proc_readvector<uint32_t>(ifs);
                std::cout << "Epoch select " << this->config.epochrd.front() << " " << this->config.epochrd.back() << std::endl;
                this->config.nprob 		=  proc_readbyte(ifs);
                this->beta                      = proc_readbyte<double>(ifs);
                //proc_readeigen(ifs, this->config.l_limit);  //NB The double vectors have to be saved using readeigen!!!
                //proc_readeigen(ifs, this->config.u_limit);
                proc_readeigen(ifs, this->weights);
                proc_readeigen(ifs, this->precision);



                this->_isset = true;

                ifs.close();
      } catch (std::ifstream::failure e) {
                throw std::runtime_error("Can't load the classifier: " + filename);
        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Wrong format for classifier: " + filename);
        }


        return this->IsSet();
}


bool BLDA::Setup(bldaconfig_t* config, const Eigen::Ref<const Eigen::VectorXd>& weights,
                                        const Eigen::Ref<const Eigen::MatrixXd>& precision, double beta) {

        this->config.filename 		= config->filename;
        this->config.subject		= config->subject;
        this->config.nclasses 		= config->nclasses;
        this->config.nfeatures 		= config->nfeatures;
        this->config.classlbs 		= config->classlbs;

        this->config.idchan 		= config->idchan;
        this->config.epochrd        = 	 config->epochrd;
        this->config.nprob 		    = config->nprob;

        this->weights = weights;
        this->precision = precision;
        this->beta = beta;

        this->_isset = true;



        return this->IsSet();
}


bool BLDA::IsSet(void) {
        if(this->_isset == false)
                throw wtk::core::Exception("The classifier is not setup");

        return this->_isset;
}


bool BLDA::Export(std::string filename, std::ios::openmode mode) {

        bool retcode = false;
        bldaconfig_t config = this->config;

        std::ofstream ofs;
        ofs.exceptions (std::ifstream::failbit | std::ifstream::badbit);


        try {
                this->IsSet();

                ofs.open(filename.c_str(), std::ios::binary | mode);

                proc_writeheader(ofs, this->_stype, this->_slabel);

                proc_writestring(ofs, config.subject);
                proc_writebyte(ofs, config.nclasses);
                proc_writebyte(ofs, config.nfeatures);
                proc_writevector<uint32_t>(ofs, config.classlbs);

                proc_writevector<uint32_t>(ofs, config.idchan);
                proc_writevector<uint32_t>(ofs, config.epochrd);


                proc_writebyte(ofs, config.nprob);
                proc_writebyte(ofs, this->beta);
                proc_writeeigen(ofs, this->weights);
                proc_writeeigen(ofs, this->precision);
                ofs.close();

                retcode = true;
        } catch (std::ifstream::failure e) {
                throw std::runtime_error("Can't save the file: " + filename);
        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Can't save the file because format: " + filename);
        }

        return retcode;
}


void BLDA::Run(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

     /*try {
        this->IsSet();
        //proc_check_dim(this->config.nfeatures, (uint32_t)in.size(), "input incorrect dimension"); //to uncomment
        //proc_check_dim(this->config.nprob, (uint32_t)out.size(), "output incorrect dimension");

        uint32_t nfeatures = in.size();

        //Eigen::VectorXd weights   = this->weights;
        //std::cout << "weights:  " << weights.size() << ", nfeatures:  " << nfeatures << std::endl;
        //std::cout << weights << std::endl;

        //Eigen::VectorXd inbias      = Eigen::VectorXd::Zero(nfeatures + 1);

        //inbias << in, 1;

        Eigen::VectorXd RawProb = Eigen::VectorXd::Zero(this->config.nprob);

        //RawProb = weights.transpose() * inbias;
        //std::cout<< "check the result BLDA -- "<< RawProb(0) << std::endl;

        out = RawProb.array();


        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Error running the classifier");
        }*/
}

double BLDA::Classify(const Eigen::Ref<const Eigen::VectorXd>& in) {



   try {
        this->IsSet();
        std::cout << "Check the dimension: in " << in.size() << " " << "n features " << this->config.nfeatures << std::endl;
        proc_check_dim(this->config.nfeatures, (uint32_t)in.size(), "input incorrect dimension"); //to uncomment


        //std::cout << "Debug nfeatures" << this->config.nfeatures << std::endl;
        //std::cout << "Debug size" << (uint32_t)in.size() << std::endl;

        double out;

        uint32_t nfeatures = in.size();

        Eigen::VectorXd weights   = this->weights;


        //debug
       //std::ofstream file;
      //file.open ("/home/gloria/workspace/whitoolkit/data/P300/test_d9_06_03_2018*/output_weights.txt");
    
       //file.close();



        Eigen::VectorXd inbias      = Eigen::VectorXd::Zero(nfeatures + 1);

        inbias << in, 1;
	
        //debug
      // std::ofstream file;
      //file.open ("/home/gloria/workspace/whitoolkit/data/P300/test_d9_06_03_2018*/output_inbias.txt");
       /*for (int i = 0; i < inbias.rows(); i++) {

                file << inbias(i);
                file << " ";

        }
       file.close();*/

        double RawProb = weights.transpose() * inbias;
        //std::cout << "check the result BLDA -- " << RawProb << std::endl;

        out = RawProb;
        return out;

        } catch (wtk::core::Exception& e) {
               throw std::runtime_error("Error running the classifier");
    }


}


double BLDA::GetVariance(const Eigen::Ref<const Eigen::VectorXd>& in) {

    try {
            this->IsSet();
            proc_check_dim(this->config.nfeatures, (uint32_t)in.size(), "input incorrect dimension");

            uint32_t nfeatures = this->config.nfeatures;

            double beta = this->beta;
            Eigen::MatrixXd precision   = this->precision;
            Eigen::VectorXd inbias 	  = Eigen::VectorXd::Zero(nfeatures + 1);

            inbias << in, 1;

            double s;

            s = inbias.transpose() * precision * inbias;
            s += 1/beta;

            return s;

    } catch (wtk::core::Exception& e) {
            throw std::runtime_error("Error running the classifier");
    }

}

void BLDA::Dump(void) {

        std::vector<uint32_t>::iterator it;
        std::vector<uint32_t> classlbs;
        std::vector<uint32_t> idchan;

        try {
                this->IsSet();

                printf("[BLDA] - Configuration:\n");
                printf("           |- Type: 			%s\n", this->_stype.c_str());
                printf("           |- Label: 			%s\n", this->_slabel.c_str());
                printf("           |- Filename: 		%s\n", this->config.filename.c_str());
                printf("           |- Subject: 			%s\n", this->config.subject.c_str());
                printf("           |- Number of classes: 	%u\n", this->config.nclasses);
                printf("           |- Number of probability/time: 	%u\n", this->config.nprob);

                classlbs = this->config.classlbs;
                printf("	     |- Class labels:    [");
                for (it=classlbs.begin(); it != classlbs.end(); ++it)
                        printf("%u ", *it);
                printf("\b]\n");

                printf("           |- Number of features: 	%u\n", this->config.nfeatures);

                idchan = this->config.idchan;
                printf("	     |- Channels:    [");
                for (it=idchan.begin(); it != idchan.end(); ++it)
                        printf("%u ", *it);
                printf("\b]\n");


        } catch (wtk::core::Exception& e) {
                printf("%s\n", e.Info().c_str());
        }

}
        }
}


#endif

