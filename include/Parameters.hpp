/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-07-25 15:53:42
 * @LastEditors: Sean
 * @LastEditTime: 2021-07-25 16:36:33
 */


#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

namespace GenLas {
    
    class Parameter {
    public:
        Parameter();
        Parameter(  const Eigen::Matrix<double, 3, 3>& rotate,
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
        Eigen::Transform<double, 3, Eigen::Affine> m_trans;

    };
};