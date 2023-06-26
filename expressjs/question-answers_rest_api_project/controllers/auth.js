const User = require('../models/User')
const CustomError = require('../helpers/error/CustomError')
const asyncErrorWrapper = require("express-async-handler")
const register = asyncErrorWrapper (async (req,res,next) => {
        //post data
        const name='Ulaş Can Demirbağ'
        const email='ulas@gmail.com'
        const password='12345'
        
        const user = await User.create({
            name,
            email,
            password
        })
        res.status(200).json({
            success:true,
            data:user
        });
})
const errorTest =(req,res,next)=>{
    //question does not exist
    return next( new SyntaxError('CUSTOM ERROR MESSAGE',400))
}

module.exports = {
    register,
    errorTest
}