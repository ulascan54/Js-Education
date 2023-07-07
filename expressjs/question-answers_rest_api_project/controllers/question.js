const Question = require('../models/Question');
const CustomError = require('../helpers/error/CustomError');
const asyncErrorWrapper = require('express-async-handler');

const askNewQuestion = asyncErrorWrapper(async (req, res, next) => {
    const information = req.body;
    console.log(information);
    const question = await Question.create({
        ...information,
        user: req.user.id,
    });
    res.status(200).json({
        success: true,
        data: question,
    });
});

const getAllQuestions = asyncErrorWrapper(async (req, res, next) => {
    let query = Question.find();
    const populate = true;
    const populateObject = {
        path: 'user',
        select: 'name profile_image',
    };
    //search
    if (req.query.search) {
        const searchObject = {};

        const regex = new RegExp(req.query.search, 'i');
        searchObject['title'] = regex;

        query = query.where(searchObject);
    }
    //populate
    if (populate) {
        query = query.populate(populateObject);
    }
    //pagination
    const page = parseInt(req.query.page) || 1;
    const limit = parseInt(req.query.limit) || 5;

    // 1 2 3 4 5 6 7 8 9 10
    // skip (2)
    // limit(2)
    // end()
    const startIndex = (page - 1) * limit;
    const endIndex = page * limit;

    const papignation = {};
    const total = await Question.countDocuments();
    if (startIndex > 0) {
        papignation.previous = {
            page: page - 1,
            limit: limit,
        };
    }

    if (endIndex < total) {
        papignation.next = {
            page: page + 1,
            limit: limit,
        };
    }
    query = query.skip(startIndex).limit(limit)

    const questions = await query;

    return res.status(200).json({
        success: true,
        count:questions.length,
        papignation: papignation,
        data: questions,
    });
});

const getSingleQuestion = asyncErrorWrapper(async (req, res, next) => {
    const { id } = req.params;
    const question = await Question.findById(id);
    return res.status(200).json({
        success: true,
        data: question,
    });
});

const editQuestion = asyncErrorWrapper(async (req, res, next) => {
    const { id } = req.params;
    const { title, content } = req.body;

    let question = await Question.findById(id);

    question.title = title;
    question.content = content;

    question = await question.save();

    return res.status(200).json({
        success: true,
        data: question,
    });
});

const deleteQuestion = asyncErrorWrapper(async (req, res, next) => {
    const { id } = req.params;
    await Question.findByIdAndDelete(id);

    return res.status(200).json({
        success: true,
        message: 'Question delete operation successful',
    });
});

const likeQuestion = asyncErrorWrapper(async (req, res, next) => {
    const { id } = req.params;
    const question = await Question.findById(id);
    if (question.likes.includes(req.user.id)) {
        return next(new CustomError('You already liked this question!', 400));
    }

    question.likes.push(req.user.id);
    await question.save();

    return res.status(200).json({
        success: true,
        data: question,
    });
});

const undoLikeQuestion = asyncErrorWrapper(async (req, res, next) => {
    const { id } = req.params;
    const question = await Question.findById(id);

    if (!question.likes.includes(req.user.id)) {
        return next(
            new CustomError(
                'You can not undo like operation for this question!',
                400
            )
        );
    }
    const index = question.likes.indexOf(req.user.id);

    question.likes.splice(index, 1);

    await question.save();

    return res.status(200).json({
        success: true,
        data: question,
    });
});

module.exports = {
    askNewQuestion,
    getAllQuestions,
    getSingleQuestion,
    editQuestion,
    deleteQuestion,
    likeQuestion,
    undoLikeQuestion,
};
