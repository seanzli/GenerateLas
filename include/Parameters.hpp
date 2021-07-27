/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-07-25 15:53:42
 * @LastEditors: Sean
 * @LastEditTime: 2021-07-27 21:38:14
 */


#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

namespace GenLas {
    
    class Parameter {
    public:

        static Parameter& instance() {
            static Parameter m_instance;
            return m_instance;
        }

        void SetLidar2body(  const Eigen::Matrix<double, 3, 3>& rotate,
                    const Eigen::Matrix<double, 3, 1>& translate,
                    const Eigen::Matrix<double, 3, 1>& check_angle) {
            m_trans = Eigen::Transform<double, 3, Eigen::Affine>::Identity();
            m_trans.rotate(rotate);
            m_trans.translate(translate);
            m_trans.rotate(Eigen::AngleAxisd(check_angle(0, 0), Eigen::Vector3d(1, 0, 0)));
            m_trans.rotate(Eigen::AngleAxisd(check_angle(1, 0), Eigen::Vector3d(0, 1, 0)));
            m_trans.rotate(Eigen::AngleAxisd(check_angle(2, 0), Eigen::Vector3d(0, 0, 1)));
        }

        Eigen::Transform<double, 3, Eigen::Affine>& getTrans() {
            return m_trans;
        }

    private:
        Parameter() {}
        
        Eigen::Transform<double, 3, Eigen::Affine> m_trans;
    };
};
