#ifndef PROC_CLASSIFIER_HPP
#define PROC_CLASSIFIER_HPP

#include <string>
#include <Eigen/Dense>

namespace wtk {
	namespace proc {

/*! \brief Pure virtual class for classifiers
 *
 * \ingroup bcitk_classifiers
 *
 * This class is used to instanciate generic classifier classes.
 * At the moment two types of classifiers are available. 
 * This is a pure virtual class, it can be instanciated only as derived class.
 * \sa Gaussian, Qda
 */

class Classifier {

	public:
		/*! \brief	Constructor
		 *  \param	type	Type of classifier
		 */
		Classifier(int type);

		/*! \brief 	Destructor 
		 */
		~Classifier(void);

		/*! \brief 	Get classifier type
		 *  \return 	The type of classifier
		 */
		int GetType(void);
	
		/*! \brief 	Set classifier name
		 *  \param name The name of classifier
		 */
		virtual void SetName(std::string name);

		/*! \brief 	Get classifier name
		 *  \return 	The name of classifier
		 */
		virtual std::string GetName(void);
		
		/*! \brief 	Pure virtual method to train the classifier.
		 *  		\todo Implementation of Train Method and to be
		 *  		defined as pure virtual method
		 */
		virtual void Train(void) {};
		
		/*! \brief 	Pure virtual method to run the classifier on
		 * 		given data
		 *  \param features 	Input features vector to be classified
		 *  \param pp		Output probabilities
		 */
		virtual void Run(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) = 0;

	public:
		/** @name 
		 * Classifier types
		 */ 
		///@{
		const static int AsLDA 		= 1;
		const static int AsQDA 		= 2;
		const static int AsGaussian 	= 3;
        const static int AsBLDA 	= 4;
        const static int AsSWLDA    = 5;
		///@}
	private:
		/*! \brief 	Classifier type
		 */
		int _type;
		
		/*! \brief 	Classifier name
		 */
		std::string _name;
	
	public: 
		/*! \brief Eigen flag to keep the memory block of the matrix
		 * aligned
		 */
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

	}
}

#endif
