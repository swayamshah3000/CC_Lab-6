pipeline {
    agent any
    stages {
        stage('Checkout SCM') {
            steps {
                checkout scm
            }
        }
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app backend/'
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 backend-app
                docker run -d --name backend2 backend-app
                sleep 3
                '''
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                script {
                    def workspace = pwd()
                    sh "docker rm -f nginx-lb || true"
                    sh "docker run -d --name nginx-lb -p 80:80 -v ${workspace}/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro nginx"
                }
            }
        }
    }
    post {
        success {
            echo 'Pipeline executed successfully!'
        }
    }
}
