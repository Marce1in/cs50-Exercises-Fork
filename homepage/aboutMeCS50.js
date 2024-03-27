
const observer = new IntersectionObserver(function (intersectionsList) {

    for (const intersection of intersectionsList){

        if (intersection.isIntersecting){
            intersection.target.classList.add('show');
            observer.unobserve(intersection.target);
        }

    }

}, {threshold: 0.2});

document.addEventListener('DOMContentLoaded', function() {
    const elementsList = document.querySelectorAll('.hidden');

    for (const element of elementsList){
        observer.observe(element);
    }
});