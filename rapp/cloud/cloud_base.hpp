#ifndef CLOUD_BASE_HPP
#define CLOUD_BASE_HPP

/**
 * @brief cloud service base class - 
 * @note defines if it is a single callable service or part of a batch
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class cloud_base
{
public:
    /**
     *  @return boolean to know if it's the service is a 
     *  single call or part of a batch
     */
    bool is_single_callable() const
    {
        return single_callable;
    }

protected:
    
    std::atomic<bool> single_callable = {false};
};

#endif
