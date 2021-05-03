#ifndef PROC_SWLDA_CPP
#define PROC_SWLDA_CPP

#include "SWLDA.hpp"

namespace wtk {
        namespace proc {


SWLDA::SWLDA(void) : Classifier(Classifier::AsSWLDA) {
        this->_stype 	= "classifier";
        this->_slabel 	= "stepwise-cnbi";

        this->_isset	= false;
}

SWLDA::~SWLDA(void) {
}


bool SWLDA::Setup(std::string filename) {

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


                this->config.idchan 		= proc_readvector<uint32_t>(ifs);
                this->config.epochrd         = proc_readvector<uint32_t>(ifs);
                this->config.nprob 		=     proc_readbyte(ifs);
                proc_readeigen(ifs, this->weights);

                this->_isset = true;

                ifs.close();
      } catch (std::ifstream::failure e) {
                throw std::runtime_error("Can't load the classifier: " + filename);
        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Wrong format for classifier: " + filename);
        }

        return this->IsSet();
}


bool SWLDA::Setup(swldaconfig_t* config, const Eigen::Ref<const Eigen::VectorXd>& weights) {

        this->config.filename 		= config->filename;
        this->config.subject		= config->subject;
        this->config.nclasses 		= config->nclasses;
        this->config.nfeatures 		= config->nfeatures;
        this->config.classlbs 		= config->classlbs;

        this->config.idchan 		= config->idchan;
        this->config.epochrd        = config->epochrd;
        this->config.nprob 		    = config->nprob;

        this->weights = weights;

        this->_isset = true;

        return this->IsSet();
}


bool SWLDA::IsSet(void) {
        if(this->_isset == false)
                throw wtk::core::Exception("The classifier is not setup");

        return this->_isset;
}


bool SWLDA::Export(std::string filename, std::ios::openmode mode) {

        bool retcode = false;
        swldaconfig_t config = this->config;

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
                proc_writeeigen(ofs, this->weights);
                ofs.close();

                retcode = true;
        } catch (std::ifstream::failure e) {
                throw std::runtime_error("Can't save the file: " + filename);
        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Can't save the file because format: " + filename);
        }

        return retcode;
}


double SWLDA::Classify(const Eigen::Ref<const Eigen::VectorXd>& in) {

   try {
        this->IsSet();
        proc_check_dim(this->config.nfeatures, (uint32_t)in.size(), "input incorrect dimension"); //to uncomment
        double out;

        uint32_t nfeatures = in.size();

        Eigen::VectorXd weights   = this->weights;

        //debug
       //std::ofstream file;
      //file.open ("/home/gloria/workspace/whitoolkit/data/P300/test_d9_06_03_2018*/output_weights.txt");
      /* for (int i = 0; i < this->weights.rows(); i++) {

                file << this->weights(i);
                file << " ";

        }
       file.close();*/

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
        std::cout << "check the result SWLDA -- " << RawProb << std::endl;

        out = RawProb;
        return out;

        } catch (wtk::core::Exception& e) {
                throw std::runtime_error("Error running the classifier");
    }


}



void SWLDA::Dump(void) {

        std::vector<uint32_t>::iterator it;
        std::vector<uint32_t> classlbs;
        std::vector<uint32_t> idchan;

        try {
                this->IsSet();

                printf("[SWLDA] - Configuration:\n");
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
