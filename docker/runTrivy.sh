#!/bin/sh

installTrivy() {
  sudo apt-get install wget apt-transport-https gnupg
  wget -qO - https://aquasecurity.github.io/trivy-repo/deb/public.key | gpg --dearmor | sudo tee /usr/share/keyrings/trivy.gpg > /dev/null
  echo "deb [signed-by=/usr/share/keyrings/trivy.gpg] https://aquasecurity.github.io/trivy-repo/deb generic main" | sudo tee -a /etc/apt/sources.list.d/trivy.list
  sudo apt-get update
  sudo apt-get install trivy
}
  

#Documentation
#https://hub.docker.com/r/aquasec/trivy/

#Install trivy if necessary
#installTrivy


#scan image
docker run aquasec/trivy image wsollers/cpp-adt:0.0.1

#generate SBOM
trivy image --format cyclonedx --output result.json wsollers/cpp-adt:0.0.1
#docker run aquasec/trivy sbom wsollers/cpp-adt 

#scan SBOM
docker run --rm -v "$(pwd)":/sbom aquasec/trivy sbom /sbom/result.json

 
#pull images if needed
#docker pull aquasec/trivy ?
#docker pull wsollers/cpp-adt:0.0.1 
